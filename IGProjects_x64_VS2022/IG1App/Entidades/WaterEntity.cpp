#include "WaterEntity.h"
#include "../IndexMesh.h"

WaterEntity::WaterEntity(GLdouble width, GLdouble depth, GLuint subdivs, Material material)
	: LowPolyEntity(material)
{
	mShader = Shader::get("water");
	mMesh = IndexMesh::generateWaterPlane(width, depth, subdivs);
}

void WaterEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh == nullptr) return;

	glm::mat4 aMat = modelViewMat * mModelMat;
	mShader->use();
	material.upload(*mShader);

	mShader->setUniform("uTime", mTime);
	mShader->setUniform("uWaveAmplitude", mAmplitude);
	mShader->setUniform("uWaveFrequency", mFrequency);

	upload(aMat);
	mMesh->render();
}

void WaterEntity::update()
{
	mTime += 0.05f;
}