#include "LowPolySphere.h"
#include "../IndexMesh.h"

LowPolySphere::LowPolySphere(GLdouble radius, GLuint nP, GLuint nM, Material material)
	: LowPolyEntity(material)
{
	mMesh = IndexMesh::generateSphere(radius, nP, nM);
}