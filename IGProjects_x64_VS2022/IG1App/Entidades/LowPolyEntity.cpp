#include "LowPolyEntity.h"

LowPolyEntity::LowPolyEntity(Material material)
	: material(material)
{
	mShader = Shader::get("light");
}

void LowPolyEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh == nullptr) return;

	glm::mat4 aMat = modelViewMat * mModelMat;
	mShader->use();
	material.upload(*mShader);

	// Wireframe uniforms
	/*mShader->setUniform("wireframeEnabled", sWireframe);
	mShader->setUniform("wireframeWidth", sWireWidth);
	mShader->setUniform("wireframeColor", sWireColor);
	*/
	upload(aMat);
	mMesh->render();
}