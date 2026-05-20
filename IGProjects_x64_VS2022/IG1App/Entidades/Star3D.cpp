#include "Star3D.h"
#include <glm/gtc/matrix_transform.hpp>

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, Texture* tex) : EntityWithTexture(tex, false)
{
	baseMat = mModelMat; 
	aMat2 = mModelMat;
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
}

void Star3D::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		
		mShader->use();
		mShader->setUniform("modulate", mModulate);
		glm::mat4 aMat1 = modelViewMat * mModelMat; // glm matrix multiplication

		upload(aMat1);

		// cuerpo principal
		if (mTexture != nullptr) 
			mTexture->bind();

		mMesh->render();

		// Apartado 27
		// rotamos para espejar la estrella
		glm::mat4 aMatA = modelViewMat * aMat2;
		aMatA = glm::rotate(aMatA, float(glm::radians(180.0f)), glm::vec3(0, 1, 0));
		upload(aMatA);

		// segunda estrella
		mMesh->render();

		if (mTexture != nullptr) 
			mTexture->unbind();

		upload(aMat1);
	}
}

// Apartado 28
void Star3D::update()
{
	glm::mat4 aMat1 = mModelMat;
	if (mMesh != nullptr) {

		// rotación eje y
		aMat1 = glm::rotate(baseMat, glm::radians(rot), glm::vec3(0, 1, 0));
		// rotación eje z segunda estrella
		aMat2 = glm::rotate(aMat1, glm::radians(-rot), glm::vec3(0, 0, 1));
		// rotación eje z cuerpo principal
		aMat1 = glm::rotate(aMat1, glm::radians(rot), glm::vec3(0, 0, 1));
	
		mModelMat = aMat1;
		rot += 4;
	}
}


void Star3D::setModelMat(glm::mat4 const& aMat) {
	Abs_Entity::setModelMat(aMat);

	aMat2 = mModelMat;
	baseMat = mModelMat;
}
