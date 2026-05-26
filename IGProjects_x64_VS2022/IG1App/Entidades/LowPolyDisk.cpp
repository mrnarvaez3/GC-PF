#include "LowPolyDisk.h"
#include "../IndexMesh.h"

LowPolyDisk::LowPolyDisk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, Material material)
	: LowPolyEntity(material)
{
	std::vector<glm::vec2> perfil(nRings);
	float intermedios = float(R - r) / float(nRings - 1);
	for (int i = 0; i < (int)nRings; i++) {
		perfil[i] = { R - intermedios * i, 0.0f };
	}
	mMesh = IndexMesh::generateByRevolution(perfil, nSamples);
}