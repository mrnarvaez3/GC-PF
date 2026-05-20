#include "RGBTriangle.h"

#include <glm/gtc/matrix_transform.hpp>

RGBTriangle::RGBTriangle(GLdouble r) : EntityWithColors()
{
	mMesh = Mesh::generateRGBTriangle(r);
	rot = 0;
}

// Apartado 13
void RGBTriangle::update()
{
	glm::mat4 aMat = mModelMat;
	if (mMesh != nullptr) {
		
		// Anti horario sobre circunferencia
		aMat = glm::rotate(glm::mat4(1.0), float(glm::radians(rot)), glm::vec3(0, 0, 1));
		// Desplazamiento
		aMat = glm::translate(aMat, glm::vec3(80, 0, 0));
		// Horario sobre si mismo
		aMat = glm::rotate(aMat, float(glm::radians(-3*rot)), glm::vec3(0, 0, 1));

		mModelMat = aMat;
		rot += 4;
	}		
}
