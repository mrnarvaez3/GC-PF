#include "LowPolyCone.h"
#include "../IndexMesh.h"

LowPolyCone::LowPolyCone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples, Material material) 
	: LowPolyEntity(material)
{
	std::vector<glm::vec2> perfil(nRings);
	for (int i = 0; i < (int)nRings; i++) {
		float t = float(i) / float(nRings - 1);
		GLdouble y = h * (1.0f - t);
		GLdouble radio = r + (1.0f - t) * (R - r);
		perfil[i] = { radio, y };
	}
	mMesh = IndexMesh::generateByRevolution(perfil, nSamples);
}