#include "IndexMesh.h"
#include <limits>

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = std::numeric_limits<GLuint>::max();

void IndexMesh::draw() const
{
	glDrawElements(
		mPrimitive, // primitiva(GL_TRIANGLES, etc.)
		vIndexes.size(), //ᜋ número de índices
		GL_UNSIGNED_INT, //ᜋ tipo de los índices
		nullptr // offset en el VBO de índices
	);
}

void IndexMesh::load() {
	Mesh::load(); 

	glBindVertexArray(mVAO);
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		vIndexes.size() * sizeof(GLuint),
		vIndexes.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void IndexMesh::unload()
{
	Mesh::unload();

	if (mIBO != NONE) glDeleteBuffers(1, &mIBO);
}

// Apartado 55
IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax)
{
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;
	int tamPerfil = profile.size();
	mesh->vVertices.reserve(nSamples * tamPerfil);
	// Genera los vertices de las muestras
	GLdouble theta1 = 2 * std:: numbers::pi / nSamples;
	for (int i = 0; i <= nSamples; ++i) { // muestra i - esima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);
		int j = 0;
		for (auto p : profile) { // rota el perfil
			mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
			// Apartado 67
			mesh->vTexCoords.emplace_back(float(i) / nSamples,1.0 - j / (tamPerfil - 1.0));
			j++;
		}
	}

	for (int i = 0; i < nSamples; ++i) {// caras i a i + 1
		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
			if (profile[j].x != 0.0f) //ᜋ triángulo inferior
				for (auto [s, t] : { std::pair{i, j}, {i, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
			if (profile[j + 1].x != 0.0f) // triángulo superior
				for (auto [s, t] : { std::pair{i, j + 1}, {i + 1, j + 1}, {i + 1, j} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	}
	mesh->mNumVertices = mesh->vVertices.size();

	// Apartado 60
	mesh->buildNormalVectors();

	return mesh;
}

// Apartado 59
void IndexMesh::buildNormalVectors()
{
	// Método de Newell

	// Se inicializan los vectores normales
	for (int j = 0; j < vVertices.size(); j++) {
		vNormals.push_back(glm::vec3(0, 0, 0));
	}

	// Se calculan promediando los vectores normales
	for (int k = 0; k < vIndexes.size(); k+= 3) {
		
		glm::vec3 normal = glm::normalize(glm::cross(vVertices[vIndexes[k+1]] - vVertices[vIndexes[k]], vVertices[vIndexes[k+2]] - vVertices[vIndexes[k]]));

		vNormals[vIndexes[k]] += normal;
		vNormals[vIndexes[k+1]] += normal;
		vNormals[vIndexes[k+2]] += normal;
	}

	// Se normalizan los vectores normales
	for (int j = 0; j < vNormals.size(); j++) {
		vNormals[j] = glm::normalize(vNormals[j]);
	}
}

// Apartado 61
IndexMesh* IndexMesh::generateIndexedBox8(GLdouble l)
{
	GLuint num = 8;
	GLuint numIndex = 36;

	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vIndexes.reserve(numIndex);

	// 8 vertices
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	// indices
	mesh->vIndexes = { 5, 7, 3, 3, 7, 1, 0, 6, 2, 2, 6, 4, 1, 7, 0, 0, 7, 6, 7, 5, 6, 6, 5, 4, 5, 3, 4, 4, 3, 2, 3, 1, 2, 2, 1, 0 };

	mesh->buildNormalVectors();

	return mesh;
}

// Apartado 64
IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
	GLuint num = 24;
	GLuint numIndex = 36;

	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vIndexes.reserve(numIndex);

	// frontal (+Z)
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);

	// trasera (-Z)
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);

	// izquierda (-X)
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);

	// derecha (+X)
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);

	// superior (+Y)
	mesh->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, l / 2);
	mesh->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	mesh->vVertices.emplace_back(-l / 2, l / 2, -l / 2);

	// inferior (-Y)
	mesh->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	mesh->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	mesh->vVertices.emplace_back(-l / 2, -l / 2, l / 2);

	// indices se colocan de 6 en 6 -> 36
	for (GLuint i = 0; i < 6; ++i) {
		GLuint b = i * 4;

		mesh->vIndexes.emplace_back(b + 0);
		mesh->vIndexes.emplace_back(b + 1);
		mesh->vIndexes.emplace_back(b + 2);

		mesh->vIndexes.emplace_back(b + 0);
		mesh->vIndexes.emplace_back(b + 2);
		mesh->vIndexes.emplace_back(b + 3);
	}

	mesh->buildNormalVectors();

	return mesh;
}

// Apartado 67
IndexMesh* IndexMesh::generateSphere(GLdouble radius, GLuint nParallel, GLuint nMeridians)
{
	std::vector<glm::vec2> perfil(nParallel);

	float rot = float(180) / float(nParallel-1);

	for (int i = 0; i < nParallel; i++) {
		perfil[i] = { radius * glm::cos(glm::radians((90 - (i * rot)))), radius * glm::sin(glm::radians((90 - (i * rot)))) };
	}

	return IndexMesh::generateByRevolution(perfil, nMeridians);
}

// --- PROYECTO FINAL ---
// Requisito 1: Malla indexada a mano (que no sea un cubo normal)
IndexMesh* IndexMesh::generateBench(GLdouble w, GLdouble sh, GLdouble bh, GLdouble d, GLdouble th)
{
	IndexMesh* mesh = new IndexMesh();
	mesh->mPrimitive = GL_TRIANGLES;

	// Es un perfil en L extruido. Son 6 vértices para el lado izquierdo y 6 para el derecho.
	mesh->mNumVertices = 12;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Vértices del lateral izquierdo (-X)
	mesh->vVertices.emplace_back(-w / 2, 0.0, d / 2);        // V0: Abajo alante
	mesh->vVertices.emplace_back(-w / 2, sh, d / 2);         // V1: Borde del asiento
	mesh->vVertices.emplace_back(-w / 2, sh, -d / 2 + th);   // V2: Esquina donde se junta asiento y respaldo
	mesh->vVertices.emplace_back(-w / 2, bh, -d / 2 + th);   // V3: Arriba del respaldo (alante)
	mesh->vVertices.emplace_back(-w / 2, bh, -d / 2);        // V4: Arriba del respaldo (atrás)
	mesh->vVertices.emplace_back(-w / 2, 0.0, -d / 2);       // V5: Abajo atrás

	// Vértices del lateral derecho (+X). Iguales pero en el lado positivo.
	mesh->vVertices.emplace_back(w / 2, 0.0, d / 2);         // V6
	mesh->vVertices.emplace_back(w / 2, sh, d / 2);          // V7
	mesh->vVertices.emplace_back(w / 2, sh, -d / 2 + th);    // V8
	mesh->vVertices.emplace_back(w / 2, bh, -d / 2 + th);    // V9
	mesh->vVertices.emplace_back(w / 2, bh, -d / 2);         // V10
	mesh->vVertices.emplace_back(w / 2, 0.0, -d / 2);        // V11

	// Meto los índices de los 12 triángulos a mano.
	// Ojo al orden (siempre en sentido antihorario) para que las normales de Newell salgan bien.
	mesh->vIndexes = {
		// Lateral izquierdo
		0, 2, 1,   0, 5, 2,   5, 4, 2,   4, 3, 2,
		// Lateral derecho
		6, 7, 8,   6, 8, 11,  11, 8, 9,  11, 9, 10,
		// Asiento cara frontal
		0, 6, 7,   0, 7, 1,
		// Asiento cara superior (donde te sientas)
		1, 7, 8,   1, 8, 2,
		// Respaldo cara frontal (donde apoyas la espalda)
		2, 8, 9,   2, 9, 3,
		// Respaldo arriba del todo
		3, 9, 10,  3, 10, 4,
		// Respaldo por detrás
		4, 10, 11, 4, 11, 5,
		// Base del banco (por si la cámara baja mucho, que no se vea hueco)
		5, 11, 6,  5, 6, 0
	};

	// Aprovecho el método de Newell que ya teníamos en la práctica anterior
	mesh->buildNormalVectors();
	return mesh;
}
// Requisito 2: Malla de revolución (Barril)
IndexMesh* IndexMesh::generateBarrel(GLdouble r, GLdouble h, GLuint nMeridians)
{
	std::vector<glm::vec2> profile;

	// Dibujo la silueta del barril (de abajo hacia arriba)
	// Como la función generateByRevolution tiene en cuenta si x==0 para cerrar la tapa, empiezo en x=0
	profile.push_back(glm::vec2(0.0f, 0.0f));         // Centro de la base de abajo
	profile.push_back(glm::vec2(r * 0.85f, 0.0f));    // Borde de la base (un poco más estrecho que la panza)
	profile.push_back(glm::vec2(r, h * 0.5f));        // La panza del barril (mitad de altura, radio máximo)
	profile.push_back(glm::vec2(r * 0.85f, h));       // Borde superior
	profile.push_back(glm::vec2(0.0f, h));            // Centro de la tapa superior (para cerrarlo)

	// Le paso mi perfil a la función que lo rota 360 grados
	return IndexMesh::generateByRevolution(profile, nMeridians);
}

// Requisito 2: Malla de revolución (Maceta)
IndexMesh* IndexMesh::generatePot(GLdouble r, GLdouble h, GLuint nMeridians)
{
	std::vector<glm::vec2> profile;

	// Silueta de una maceta rústica
	profile.push_back(glm::vec2(0.0f, 0.0f));         // Centro de la base
	profile.push_back(glm::vec2(r * 0.6f, 0.0f));     // Borde de la base (las macetas son estrechas por abajo)
	profile.push_back(glm::vec2(r, h * 0.7f));        // Se va abriendo hasta arriba
	profile.push_back(glm::vec2(r * 0.9f, h * 0.8f)); // Cuello un poco más hundido
	profile.push_back(glm::vec2(r * 0.95f, h));       // Reborde superior
	profile.push_back(glm::vec2(0.0f, h));            // Lo cierro por arriba plano (simulando que está llena de tierra)

	return IndexMesh::generateByRevolution(profile, nMeridians);
}
