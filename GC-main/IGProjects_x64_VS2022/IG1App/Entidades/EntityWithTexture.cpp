#include "EntityWithTexture.h"

EntityWithTexture::EntityWithTexture(Texture* texture, bool modulate)
{
	mTexture = texture;
	mModulate = modulate;
	mShader = Shader::get("texture");
}

void EntityWithTexture::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		mShader->use();
		mShader->setUniform("modulate", mModulate);
		upload(aMat);
		if (mTexture != nullptr) {
			mTexture->bind();
			mMesh->render();
			mTexture->unbind();
		}
		else
			mMesh->render();
	}
}
