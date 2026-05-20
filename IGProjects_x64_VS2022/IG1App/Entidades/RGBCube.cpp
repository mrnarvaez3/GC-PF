#include "RGBCube.h"
#include <glm/gtc/matrix_transform.hpp>

RGBCube::RGBCube(GLdouble length) : length(length)
{
	mMesh = Mesh::generateRGBCubeTriangles(length);
}

// Apartado 17
void RGBCube::update()
{
	if (mMesh != nullptr) {
		glm::mat4 aMat = mModelMat;
		rot += 5;
		
		// En cada paso desplazamos al centro rotamos y devolvemos a la posicion
		if (rot <= 180) { // Primer tramo
			aMat = glm::translate(aMat, glm::vec3(-length / 2, -length / 2, length / 2));
			aMat = glm::rotate(glm::mat4(1.0), float(glm::radians(rot)), glm::vec3(1, 0, 0));
			aMat = glm::translate(aMat, glm::vec3(length / 2, length / 2, -length / 2));
		}
		else if (rot <= 360 && rot > 180) { // Segundo tramo
			aMat = glm::translate(aMat, glm::vec3(length / 2, -length / 2, -length / 2));
			aMat = glm::rotate(glm::mat4(1.0), float(glm::radians(-1*rot)), glm::vec3(0, 0, -1));
			aMat = glm::translate(aMat, glm::vec3(-length / 2, length / 2, length / 2));
		}
		else if (rot <= 540 && rot > 360) { // Tercer tramo
			aMat = glm::translate(aMat, glm::vec3(length / 2, -length / 2, -length / 2));
			aMat = glm::rotate(glm::mat4(1.0), float(glm::radians(-1*rot)), glm::vec3(0, -1, 0));
			aMat = glm::translate(aMat, glm::vec3(-length / 2, length / 2, length / 2));
		}
		else { // Reiniciamos la rotación, también se podría hacer con modulo
			rot = 0;
		}	

		mModelMat = aMat;	
	}
}
