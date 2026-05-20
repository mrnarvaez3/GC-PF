#include "Ground.h"
#include <glm/gtc/matrix_transform.hpp>

Ground::Ground(GLdouble w, GLdouble h, Texture* texture, bool modulate) : EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 4, 4);
	mModelMat = glm::rotate(glm::mat4(1.0), float(glm::radians(-90.0f)), glm::vec3(1, 0, 0));
}
