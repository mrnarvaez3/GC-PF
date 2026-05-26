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
