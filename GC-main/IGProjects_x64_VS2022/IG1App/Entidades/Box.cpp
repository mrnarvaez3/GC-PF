#include "Box.h"
#include <glm/gtc/matrix_transform.hpp>

Box::Box(GLdouble length, Texture* tex, Texture* tex2, bool modulate) : EntityWithTexture(tex, modulate), length(length), mTexture2(tex2)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
	mMesh1 = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mMesh1->load();
	
	mMesh2 = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mMesh2->load();

	// tapa
	// desplazamos a su posición
	aMat1 = glm::translate(mModelMat, glm::vec3(0, length / 2, 0));
	// rotamos su posición
	aMat1 = glm::rotate(aMat1, float(glm::radians(-90.0f)), glm::vec3(1, 0, 0));

	// fondo
	// desplazamos a su posición
	aMat2 = glm::translate(mModelMat, glm::vec3(0, -length / 2, 0));
	// rotamos su posición (rotación opuesta tapa)
	aMat2 = glm::rotate(aMat2, float(glm::radians(90.0f)), glm::vec3(1, 0, 0));
}

Box::~Box()
{
	delete(mMesh);
	mMesh = nullptr;
	mMesh1->unload();
	delete(mMesh1);
	mMesh1 = nullptr;
	mMesh2->unload();
	delete(mMesh2);
	mMesh2 = nullptr;
}

void Box::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr && mMesh1 != nullptr && mMesh2 != nullptr) {
		glEnable(GL_CULL_FACE);
		mShader->use();
		mShader->setUniform("modulate", mModulate);
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		glm::mat4 aMatT = modelViewMat * aMat1; // glm matrix multiplication
		glm::mat4 aMatF = modelViewMat * aMat2; // glm matrix multiplication
		
		upload(aMat);

		if (mTexture != nullptr && mTexture2 != nullptr) {
			// Textura 1 contorno - tapa - fondo
			glCullFace(GL_BACK);
			mTexture->bind();
			// contorno
			mMesh->render();

			// tapa
			upload(aMatT);
			mMesh1->render();

			// fondo
			upload(aMatF);
			mMesh2->render();

			mTexture->unbind();

			// reiniciamos estado matriz de modelado para el contorno
			upload(aMat); 
			glCullFace(GL_FRONT);
			// Textura 2 contorno - tapa - fondo
			mTexture2->bind();
			// contorno
			mMesh->render();

			// tapa
			upload(aMatT);
			mMesh1->render();

			// fondo
			upload(aMatF);
			mMesh2->render();

			mTexture2->unbind();
			glDisable(GL_CULL_FACE);
		}
		else
			mMesh->render();

		// reiniciamos estado matriz de modelado para el contorno
		upload(aMat);
	}
}

// Apartado 31
void Box::update()
{
	glm::mat4 aMat = mModelMat;

	if (mMesh != nullptr) {
		if (rot < 180 && up)
			rot += 4;
		else if (rot > 0 && !up)
			rot -= 4;
		else
			up = !up;

		// radio
		float r = length / 2.0f;
		// angulo
		float angle = glm::radians(rot);

		// desplazamiento x e y
		// alternancia entre lenght/2 y lenght
		float alt = r * sin(angle);
		// desplazamiento para mantener la visagra r - r * cos(a) -> inicialmente x = r
		float offset = r * (1 - cos(angle));

		// movimiento tapa
		aMat1 = glm::translate(mModelMat, glm::vec3(-offset, length / 2 + alt, 0));
		aMat1 = glm::rotate(aMat1, float(glm::radians(-90.0f)), glm::vec3(1, 0, 0));
		aMat1 = glm::rotate(aMat1, float(glm::radians(-rot)), glm::vec3(0, 1, 0));
	}
	
}

void Box::setModelMat(glm::mat4 const& aMat) {
	Abs_Entity::setModelMat(aMat);

	// tapa
	// desplazamos a su posición
	aMat1 = glm::translate(mModelMat, glm::vec3(0, length / 2, 0));
	// rotamos su posición
	aMat1 = glm::rotate(aMat1, float(glm::radians(-90.0f)), glm::vec3(1, 0, 0));

	// fondo
	// desplazamos a su posición
	aMat2 = glm::translate(mModelMat, glm::vec3(0, -length / 2, 0));
	// rotamos su posición (rotación opuesta tapa)
	aMat2 = glm::rotate(aMat2, float(glm::radians(90.0f)), glm::vec3(1, 0, 0));
}
