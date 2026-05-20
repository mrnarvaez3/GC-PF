#include "Cube.h"

Cube::Cube(GLdouble length) : SingleColorEntity(glm::vec4(0,0,0,1))
{
	mMesh = Mesh::generateCube(length);
}

// Apartado 15
void Cube::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);
		mShader->use();
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		upload(aMat);

		// Linea - FRONT / Puntos - BACK
		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		mMesh->render();

		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mMesh->render();

		glCullFace(GL_FRONT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDisable(GL_CULL_FACE);
	}
}
