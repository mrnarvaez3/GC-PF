#include "Disk.h"
#include "../IndexMesh.h"

Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, Material material) : ColorMaterialEntity(material)
{
	// r = radio interior
	// R = radio exterior
	// n = numero de muestras
	std::vector<glm::vec2> perfil(nRings);

	float intermedios = float(R-r) / float(nRings-1);
	for (int i = 0; i < nRings; i++) {
		perfil[i] = { R - intermedios * i, 0.0f };
	}
	mMesh = IndexMesh::generateByRevolution(perfil, nSamples);
}
