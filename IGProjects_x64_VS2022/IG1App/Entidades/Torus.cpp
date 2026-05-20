#include "Torus.h"
#include "../IndexMesh.h"

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples, Material material) : ColorMaterialEntity(material)
{
	std::vector<glm::vec2> perfil(nPoints);

	float rot = float(360) / float(nPoints-1);
	// perfil
	for (int i = 0; i < nPoints; i++) {
		perfil[i] = { r * glm::cos(glm::radians((90 - (i * rot)))) + R , r * glm::sin(glm::radians((90 - (i * rot)))) }; // o más puntos
	}

	mMesh = IndexMesh::generateByRevolution(perfil, nSamples);
}
