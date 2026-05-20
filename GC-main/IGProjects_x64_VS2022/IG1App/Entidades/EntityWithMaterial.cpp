#include "EntityWithMaterial.h"

EntityWithMaterial::EntityWithMaterial()
{
	mShader = Shader::get("light");
}

void EntityWithMaterial::setMaterial(const Material& m)
{
	material = m;
}

void EntityWithMaterial::render(const glm::mat4& modelViewMat) const
{
	mShader->use();
	// Carga los atributos del material en la GPU
	material.upload(*mShader);
	upload(modelViewMat * mModelMat);
	mMesh->render();
}
