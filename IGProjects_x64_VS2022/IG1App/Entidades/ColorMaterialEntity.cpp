#include "ColorMaterialEntity.h"

ColorMaterialEntity::ColorMaterialEntity(Material material) : EntityWithMaterial()
{
	setMaterial(material);
}

void ColorMaterialEntity::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		// Usamos el shader para aplicar el color
		mShader->use();
		material.upload(*mShader);
		upload(modelViewMat * mModelMat);
		mMesh->render();
		// Apartado 63 
		// para depurar mostrar las normales en base a un atributo -> mShowNormals
		if (mShowNormals) {
			Shader* shader = Shader::get("normals");
			shader->use();
			shader->setUniform("modelView", aMat);
			mMesh->render();
		}	
	}
}

void ColorMaterialEntity::toggleShowNormals()
{
	mShowNormals = !mShowNormals;
}

