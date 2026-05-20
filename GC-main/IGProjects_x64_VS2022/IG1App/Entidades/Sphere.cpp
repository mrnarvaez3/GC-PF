#include "Sphere.h"
#include "../IndexMesh.h"

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians, Material material) : ColorMaterialEntity(material)
{
	mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}
