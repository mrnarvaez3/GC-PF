#include "Lake.h"
#include "../IndexMesh.h"

Lake::Lake(GLdouble R, GLuint nRings, GLuint nSamples, Texture* texture) : EntityWithTexture(texture, false)
{
	// r = radio interior
	// R = radio exterior
	// n = numero de muestras
	std::vector<glm::vec2> perfil(nRings);

	float intermedios = float(R) / float(nRings - 1);
	for (int i = 0; i < nRings; i++) {
		perfil[i] = { R - intermedios * i, 0.0f };
	}
	mMesh = IndexMesh::generateByRevolution(perfil, nSamples);
}
