#include "RGBRectangle.h"

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}

// Apartado 9
void RGBRectangle::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);
		mShader->use();
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		upload(aMat);

		// Culling rellenamos por la cara back dibujamos línea cara front
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		// Lo devolvemos todo al estado base
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDisable(GL_CULL_FACE);
	}
}
