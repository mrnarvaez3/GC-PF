#include "SingleColorEntity.h"

SingleColorEntity::SingleColorEntity(glm::vec4 color)
{
	mColor = color;
	// usamos shader simple
	mShader = Shader::get("simple");
}

void SingleColorEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		// Usamos el shader para aplicar el color
		mShader->use();
		mShader->setUniform("color", mColor);
		upload(aMat);
		mMesh->render();
	}
}

void SingleColorEntity::setColor(glm::vec4 nColor)
{
	mColor = nColor;
}

glm::vec4 SingleColorEntity::getColor()
{
	return mColor;
}
