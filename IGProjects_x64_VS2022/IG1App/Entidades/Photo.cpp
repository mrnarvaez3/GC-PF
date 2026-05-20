#include "Photo.h"
#include <glm/gtc/matrix_transform.hpp>

Photo::Photo(GLdouble w, GLdouble h, Texture * texture, bool modulate) : EntityWithTexture(texture, modulate), w(w), h(h)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
}

void Photo::update()
{
	mTexture->loadColorBuffer(800,600);
}
