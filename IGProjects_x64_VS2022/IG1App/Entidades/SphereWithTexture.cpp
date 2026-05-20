#include "SphereWithTexture.h"
#include "../IndexMesh.h"

#include <glm/gtc/matrix_transform.hpp>

SphereWithTexture::SphereWithTexture(GLdouble radius, GLuint nParallel, GLuint nMeridians, Texture* texture, bool modulate) : EntityWithTexture(texture, modulate)
{
	mMesh = IndexMesh::generateSphere(radius, nParallel, nMeridians);
}
