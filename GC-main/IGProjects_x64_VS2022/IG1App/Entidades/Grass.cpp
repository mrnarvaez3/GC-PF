#include "Grass.h"
#include <glm/gtc/matrix_transform.hpp>

Grass::Grass(GLdouble w, GLdouble h, Texture* texture, bool modulate) : EntityWithTexture(texture, modulate)
{
	mMesh = Mesh::generateRectangleTexCor(w, h, 1, 1);
	mShader = Shader::get("texture:texture_alpha");
}

void Grass::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {

		mShader->use();
		mShader->setUniform("modulate", mModulate);
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		upload(aMat);

		// cuerpo principal
		if (mTexture != nullptr)
			mTexture->bind();

		mMesh->render();

		
		// segundo cesped
		aMat = glm::rotate(aMat, float(glm::radians(50.0f)), glm::vec3(0, 1, 0));
		upload(aMat);

		mMesh->render();

		// tercer cesped
		aMat = glm::rotate(aMat, float(glm::radians(100.0f)), glm::vec3(0, 1, 0));
		upload(aMat);

		mMesh->render();

		if (mTexture != nullptr) 
			mTexture->unbind();

		upload(aMat);
	}
}