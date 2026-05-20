#include "Mesh.h"

using namespace std;
using namespace glm;

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
 , mTCO(NONE)
 , mNBO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded

	
	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}
		if (vTexCoords.size() > 0) {
			glGenBuffers(1, &mTCO);
			glBindBuffer(GL_ARRAY_BUFFER, mTCO);
			glBufferData(GL_ARRAY_BUFFER,
				vTexCoords.size() * sizeof(vec2),
				vTexCoords.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
				sizeof(vec2), nullptr);
			glEnableVertexAttribArray(2);
		}
		if (vNormals.size() > 0) { //upload normals
			glGenBuffers(1, &mNBO);
			glBindBuffer(GL_ARRAY_BUFFER, mNBO);
			glBufferData(GL_ARRAY_BUFFER,
				vNormals.size() * sizeof(vec3),
				vNormals.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
				sizeof(vec3), nullptr);
			glEnableVertexAttribArray(3);
		}
	}
}

void
Mesh::unload()
{
	if (mTCO != NONE) glDeleteBuffers(1, &mTCO);
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		glDeleteBuffers(1, &mNBO);
		mVAO = NONE;
		mVBO = NONE;
		mNBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}
	}
}

// Apartado 2
Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Desplazamineto de los puntos en la circunferencia
	// Importante que sean float para la correcta división
	float rot = float(360) / float(num);
	// Se reccorre el número de vertices para colocarlos
	for (int i = 0; i < num; i++) {
		mesh->vVertices.emplace_back(r * glm::cos(glm::radians((90 + (i * rot)))), r * glm::sin(glm::radians((90 + (i * rot)))), 0.0f);
	}

	return mesh;
}

// Apartado 7
Mesh* Mesh::generateRGBTriangle(GLdouble r)
{
	GLuint num = 3;
	
	Mesh* mesh = generateRegularPolygon(num, r);

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vColors.emplace_back(1,0,0,1);
	mesh->vColors.emplace_back(0,1,0,1);
	mesh->vColors.emplace_back(0,0,1,1);

	return mesh;
}

// Apartado 8
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h)
{
	GLuint num = 4;

	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Colocamos los vertices
	/*
	3****************1
	*			   ***
	*		     **	 *
	*		   **	 * 
	*		 **		 *
	*	   **		 *
	*	 **			 *
	*  **			 *
	***				 *
	2****************0
	*/
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0);
	mesh->vVertices.emplace_back(w / 2, h / 2, 0);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, 0);
	mesh->vVertices.emplace_back(-w / 2, h / 2, 0);

	return mesh;
}

// Apartado 8
Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h)
{
	// Generamos la malla del rectángulo
	Mesh* mesh = generateRectangle(w, h);

	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->vColors.reserve(mesh->mNumVertices);

	// Añadimos el color a los vertices
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);

	return mesh;
}

// Apartado 15
Mesh* Mesh::generateCube(GLdouble length)
{
	GLuint num = 36;

	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// frontal
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(-length/2, length / 2, length / 2);
	mesh->vVertices.emplace_back(-length/2, -length / 2, length / 2);
	// trasera
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);
	// izquierda
	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2);
	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2);
	// derecha
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2);
	// superior
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, length / 2, -length / 2);
	mesh->vVertices.emplace_back(-length / 2, length / 2, -length / 2);
	// inferior
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2);
	mesh->vVertices.emplace_back(-length / 2, -length / 2, length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, length / 2);
	mesh->vVertices.emplace_back(-length / 2, -length / 2, -length / 2);
	mesh->vVertices.emplace_back(length / 2, -length / 2, -length / 2);

	return mesh;
}


// Apartado 16
Mesh* Mesh::generateRGBCubeTriangles(GLdouble length)
{
	Mesh* mesh = generateCube(length);

	mesh->vColors.reserve(mesh->mNumVertices);

	// frontal - rojo
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	// trasera - rojo
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	mesh->vColors.emplace_back(1, 0, 0, 1);
	// izquierda - verde
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	// derecha - verde
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	mesh->vColors.emplace_back(0, 1, 0, 1);
	// superior - azul
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	// inferior - azul
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);
	mesh->vColors.emplace_back(0, 0, 1, 1);

	return mesh;
}

// Apartado 20
Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generateRectangle(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// asignación coordenadas de textura
	mesh->vTexCoords.emplace_back(rw, 0);
	mesh->vTexCoords.emplace_back(rw, rh);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(0, rh);

	return mesh;
}

// Apartado 23
Mesh* Mesh::generateBoxOutline(GLdouble length)
{
	GLuint num = 10;

	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble auxL = length / 2;

	// frontal
	mesh->vVertices.emplace_back(auxL, -auxL, auxL);
	mesh->vVertices.emplace_back(auxL, auxL, auxL);
	mesh->vVertices.emplace_back(-auxL, -auxL, auxL);
	mesh->vVertices.emplace_back(-auxL, auxL, auxL);

	// izquierda
	mesh->vVertices.emplace_back(-auxL, -auxL, -auxL);
	mesh->vVertices.emplace_back(-auxL, auxL, -auxL);

	// trasera
	mesh->vVertices.emplace_back(auxL, -auxL, -auxL);
	mesh->vVertices.emplace_back(auxL, auxL, -auxL);

	// derecha
	mesh->vVertices.emplace_back(auxL, -auxL, auxL);
	mesh->vVertices.emplace_back(auxL, auxL, auxL);

	return mesh;
}

Mesh* Mesh::generateBoxOutlineTexCor(GLdouble length)
{
	// asigna las coordenadas de textura de boxoutline
	Mesh* mesh = generateBoxOutline(length);
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// frontal
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(0, 1);

	// izquierda
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(1, 1);

	// trasera
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(0, 1);

	// derecha
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(1, 1);

	return mesh;
}

// Apartado 26
Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h)
{
	GLuint num = (2*np) + 2;

	Mesh* mesh = new Mesh();
	mesh->mNumVertices = num;
	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->vVertices.reserve(mesh->mNumVertices);

	// central
	mesh->vVertices.emplace_back(0, 0, 0);

	// Desplazamineto de los puntos en la circunferencia
	// Importante que sean float para la correcta división
	float rot = float(360) / float(np);
	// Se reccorre el número de vertices para colocarlos
	for (int i = 0; i < 2*np; i++) {
		mesh->vVertices.emplace_back(re * glm::cos(glm::radians((90 + (i * rot)))), re * glm::sin(glm::radians((90 + (i * rot)))), h);
		mesh->vVertices.emplace_back(re/2 * glm::cos(glm::radians(((90+rot/2) + (i * rot)))), re/2 * glm::sin(glm::radians(((90 + rot / 2) + (i * rot)))), h);
	}
	// cierre
	mesh->vVertices.emplace_back(re * glm::cos(glm::radians((90 + (0*rot)))), re * glm::sin(glm::radians((90 + (0*rot)))), h);

	return mesh;
}

// Apartado 29
Mesh* Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = generateStar3D(re, np, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	// centro
	mesh->vTexCoords.emplace_back(0.5f, 0.5f);

	// estado incial
	float x = 0.75;
	float y = 1;

	// casos para colocar la textura de manera regular
	for (int i = 0; i < 2 * np; i++)
	{
 		if (x > 0 && y == 1)
			x -= 0.25;
		else if (x == 0 && y > 0)
			y -= 0.25;
		else if (x < 1 && y == 0)
			x += 0.25;
		else
			y += 0.25;

		mesh->vTexCoords.emplace_back(x,y);
	}
	// cerramos con el centro
	mesh->vTexCoords.emplace_back(0.5, 0.5);

	return mesh;
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}
