#include "Lantern.h"
#include "LowPolyCone.h"
#include "LowPolyDisk.h"
#include "LowPolySphere.h"
#include "LowPolyBox.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Lantern::Lantern(GLdouble size) : CompoundEntity()
{
	int lp = 6;

	// Hierro forjado
	Material ironMat(glm::vec3(0.35f, 0.35f, 0.38f));
	ironMat.setAmb({ 0.2f, 0.2f, 0.22f });
	ironMat.setDiff({ 0.35f, 0.35f, 0.38f });
	ironMat.setSpec({ 0.4f, 0.4f, 0.45f });
	ironMat.setExp(16.0f);

	// Cristal luminoso amarillo brillante
	Material glassMat(glm::vec3(1.0f, 0.85f, 0.3f));
	glassMat.setAmb({ 0.9f, 0.75f, 0.3f });
	glassMat.setDiff({ 1.0f, 0.85f, 0.3f });
	glassMat.setSpec({ 0.9f, 0.8f, 0.4f });
	glassMat.setExp(64.0f);

	// Soporte vertical pegado a la pared
	GLfloat posteR = size * 0.04f;
	GLfloat posteH = size * 0.7f;
	LowPolyCone* poste = new LowPolyCone(posteH, posteR, posteR, 4, lp, ironMat);
	addEntity(poste);

	// Brazo horizontal que sale de la pared (hacia +Z)
	GLfloat brazoL = size * 0.4f;
	LowPolyCone* brazo = new LowPolyCone(brazoL, posteR * 0.8f, posteR * 0.8f, 4, lp, ironMat);
	glm::mat4 bMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, posteH, 0));
	bMat = glm::rotate(bMat, glm::radians(90.0f), glm::vec3(1, 0, 0));
	brazo->setModelMat(bMat);
	addEntity(brazo);

	// Posicion del farol: al final del brazo
	GLfloat farolX = 0;
	GLfloat farolY = posteH - size * 0.08f;
	GLfloat farolZ = brazoL;

	// Luz puntual en la posicion del cristal
	mLight = new PosLight(1);
	mLight->setPosition(glm::vec3(farolX, farolY, farolZ));
	mLight->setAmb({ 0.2f, 0.15f, 0.05f });
	mLight->setDiff({ 1.0f, 0.8f, 0.4f });
	mLight->setSpec({ 1.0f, 0.9f, 0.5f });
	mLight->setAttenuation(1.0f, 0.005f, 0.0001f);
	gLights.push_back(mLight);

	// Techo del farol (conito)
	LowPolyCone* techoF = new LowPolyCone(size * 0.1f, size * 0.12f, 0, 4, lp, ironMat);
	techoF->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(farolX, farolY + size * 0.08f, farolZ)));
	addEntity(techoF);

	// Cuerpo de cristal (esfera luminosa, mas grande)
	LowPolySphere* bulb = new LowPolySphere(size * 0.09f, 6, 6, glassMat);
	bulb->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(farolX, farolY, farolZ)));
	addEntity(bulb);

	// Base del farol
	LowPolyDisk* baseF = new LowPolyDisk(size * 0.08f, 0, 3, lp, ironMat);
	baseF->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(farolX, farolY - size * 0.09f, farolZ)));
	addEntity(baseF);

}

void Lantern::update()
{
	mFlickerTime += 0.15f;
	float flicker = 0.85f + 0.15f * sinf(mFlickerTime * 3.7f)
		* cosf(mFlickerTime * 5.3f);
	if (flicker < 0.6f) flicker = 0.6f;
	mLight->setDiff({ flicker * 1.0f, flicker * 0.8f, flicker * 0.4f });
}

void Lantern::lightOnOff()
{
	mLight->setEnabled(!mLight->enabled());
}