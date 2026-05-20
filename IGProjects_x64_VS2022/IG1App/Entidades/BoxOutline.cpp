#include "BoxOutline.h"

BoxOutline::BoxOutline(GLdouble length, Texture* texture, Texture* tex2, bool modulate) : EntityWithTexture(texture, modulate), length(length), mTexture2(tex2)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

// Apartado 25
void BoxOutline::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);
		mShader->use();
		mShader->setUniform("modulate", mModulate);
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		upload(aMat);

		if (mTexture != nullptr && mTexture2 != nullptr) {

			// Textura papel / Textura interior
			glCullFace(GL_BACK);
			mTexture->bind();
			mMesh->render();
			mTexture->unbind();

			glCullFace(GL_FRONT);
			mTexture2->bind();
			mMesh->render();
			mTexture2->unbind();

			glDisable(GL_CULL_FACE);			
		}
		else
			mMesh->render();
	}
}


