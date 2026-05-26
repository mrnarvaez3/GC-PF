#include "Skybox.h"
#include <glm/gtc/matrix_transform.hpp>

Skybox::Skybox(GLdouble size, Texture* texture, bool modulate)
	: EntityWithTexture(texture, modulate), mSize(size)
{
	mMesh = Mesh::generateRectangleTexCor(size, size, 1, 1);
}

void Skybox::render(const glm::mat4& modelViewMat) const
{
	if (mMesh == nullptr || mTexture == nullptr) return;

	glDepthMask(GL_FALSE);

	mShader->use();
	mShader->setUniform("modulate", mModulate);
	mTexture->bind();

	GLfloat s = (GLfloat)(mSize / 2.0);
	glm::mat4 base = modelViewMat * mModelMat;
	glm::mat4 face;

	// -Z
	face = glm::translate(base, glm::vec3(0, 0, -s));
	upload(face);
	mMesh->render();

	// +Z
	face = glm::translate(base, glm::vec3(0, 0, s));
	face = glm::rotate(face, glm::radians(180.0f), glm::vec3(0, 1, 0));
	upload(face);
	mMesh->render();

	// -X
	face = glm::translate(base, glm::vec3(-s, 0, 0));
	face = glm::rotate(face, glm::radians(90.0f), glm::vec3(0, 1, 0));
	upload(face);
	mMesh->render();

	// +X
	face = glm::translate(base, glm::vec3(s, 0, 0));
	face = glm::rotate(face, glm::radians(-90.0f), glm::vec3(0, 1, 0));
	upload(face);
	mMesh->render();

	// +Y
	face = glm::translate(base, glm::vec3(0, s, 0));
	face = glm::rotate(face, glm::radians(90.0f), glm::vec3(1, 0, 0));
	upload(face);
	mMesh->render();

	// -Y
	face = glm::translate(base, glm::vec3(0, -s, 0));
	face = glm::rotate(face, glm::radians(-90.0f), glm::vec3(1, 0, 0));
	upload(face);
	mMesh->render();

	mTexture->unbind();
	glDepthMask(GL_TRUE);
}