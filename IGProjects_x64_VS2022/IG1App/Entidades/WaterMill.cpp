#include "WaterMill.h"
#include "LowPolyCone.h"
#include "LowPolyBox.h"
#include "LowPolyDisk.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

// Cubeta abierta: 5 caras
class Bucket : public CompoundEntity
{
public:
	Bucket(float w, float h, float d, Material mat)
	{
		float t = h * 0.15f; // grosor de las paredes

		// Fondo (cara exterior)
		LowPolyBox* fondo = new LowPolyBox(1, mat);
		fondo->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(0, h / 2, 0))
			* glm::scale(glm::mat4(1.0f), glm::vec3(w, t, d)));
		addEntity(fondo);

		// Pared izquierda
		LowPolyBox* izq = new LowPolyBox(1, mat);
		izq->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(-w / 2 + t / 2, 0, 0))
			* glm::scale(glm::mat4(1.0f), glm::vec3(t, h, d)));
		addEntity(izq);

		// Pared derecha
		LowPolyBox* der = new LowPolyBox(1, mat);
		der->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(w / 2 - t / 2, 0, 0))
			* glm::scale(glm::mat4(1.0f), glm::vec3(t, h, d)));
		addEntity(der);

		// Pared frontal
		LowPolyBox* front = new LowPolyBox(1, mat);
		front->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, d / 2 - t / 2))
			* glm::scale(glm::mat4(1.0f), glm::vec3(w, h, t)));
		addEntity(front);

		// Pared trasera
		LowPolyBox* back = new LowPolyBox(1, mat);
		back->setModelMat(
			glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -d / 2 + t / 2))
			* glm::scale(glm::mat4(1.0f), glm::vec3(w, h, t)));
		addEntity(back);
	}
};

WaterMill::WaterMill(GLdouble radius) : CompoundEntity()
{
	Material woodMat(glm::vec3(0.5f, 0.32f, 0.15f));
	woodMat.setAmb({ 0.25f, 0.16f, 0.08f });
	woodMat.setDiff({ 0.5f, 0.32f, 0.15f });
	woodMat.setSpec({ 0.05f, 0.04f, 0.02f });
	woodMat.setExp(4.0f);

	Material darkWoodMat(glm::vec3(0.35f, 0.2f, 0.1f));
	darkWoodMat.setAmb({ 0.18f, 0.1f, 0.05f });
	darkWoodMat.setDiff({ 0.35f, 0.2f, 0.1f });
	darkWoodMat.setSpec({ 0.04f, 0.03f, 0.02f });
	darkWoodMat.setExp(4.0f);

	Material metalMat(glm::vec3(0.4f, 0.4f, 0.45f));
	metalMat.setAmb({ 0.2f, 0.2f, 0.22f });
	metalMat.setDiff({ 0.4f, 0.4f, 0.45f });
	metalMat.setSpec({ 0.5f, 0.5f, 0.55f });
	metalMat.setExp(24.0f);

	int lp = 6;
	int numSpokes = 8;
	float R = (float)radius;
	float spokeR = R * 0.03f;
	float rimR = R * 0.04f;
	float depth = R * 0.15f;

	// === Rueda (nodo que rota):
	mWheel = new CompoundEntity();
	addEntity(mWheel);

	// --- Eje central:
	LowPolyCone* axle = new LowPolyCone(depth * 2, R * 0.05f, R * 0.05f, 4, lp, metalMat);
	glm::mat4 axleMat = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, depth));
	axleMat = glm::rotate(axleMat, glm::radians(90.0f), glm::vec3(1, 0, 0));
	axle->setModelMat(axleMat);
	mWheel->addEntity(axle);

	// --- Radios:
	for (int i = 0; i < numSpokes; i++) {
		float angle = (float)i * 360.0f / numSpokes;
		LowPolyCone* spoke = new LowPolyCone(R * 0.82f, spokeR, spokeR, 4, lp, woodMat);
		glm::mat4 sMat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 0, 1));
		spoke->setModelMat(sMat);
		mWheel->addEntity(spoke);
	}

	// --- Doble aro exterior ---
	int numRimSegs = 16;
	for (int ring = 0; ring < 2; ring++) {
		float z = (ring == 0) ? depth * 0.4f : -depth * 0.4f;

		for (int i = 0; i < numRimSegs; i++) {
			float a0 = (float)i * 360.0f / numRimSegs;
			float a1 = (float)(i + 1) * 360.0f / numRimSegs;

			float x0 = R * 0.82f * cosf(glm::radians(a0));
			float y0 = R * 0.82f * sinf(glm::radians(a0));
			float x1 = R * 0.82f * cosf(glm::radians(a1));
			float y1 = R * 0.82f * sinf(glm::radians(a1));

			float cx = (x0 + x1) / 2.0f;
			float cy = (y0 + y1) / 2.0f;
			float segLen = sqrtf((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
			float segAngle = atan2f(y1 - y0, x1 - x0);

			LowPolyCone* seg = new LowPolyCone(segLen, rimR, rimR, 4, lp, darkWoodMat);
			glm::mat4 rMat = glm::translate(glm::mat4(1.0f), glm::vec3(cx, cy, z));
			rMat = glm::rotate(rMat, segAngle, glm::vec3(0, 0, 1));
			rMat = glm::rotate(rMat, glm::radians(-90.0f), glm::vec3(0, 0, 1));
			rMat = glm::translate(rMat, glm::vec3(0, -segLen / 2.0f, 0));
			seg->setModelMat(rMat);
			mWheel->addEntity(seg);
		}
	}

	// --- Travesanos entre aros ---
	for (int i = 0; i < numSpokes; i++) {
		float angle = (float)i * 360.0f / numSpokes;
		float px = R * 0.82f * cosf(glm::radians(angle));
		float py = R * 0.82f * sinf(glm::radians(angle));

		LowPolyCone* trav = new LowPolyCone(depth * 0.8f, rimR, rimR, 4, lp, darkWoodMat);
		glm::mat4 tMat = glm::translate(glm::mat4(1.0f), glm::vec3(px, py, depth * 0.4f));
		tMat = glm::rotate(tMat, glm::radians(90.0f), glm::vec3(1, 0, 0));
		trav->setModelMat(tMat);
		mWheel->addEntity(trav);
	}

	// --- Cubetas abiertas ---
	float bucketW = R * 0.2f;
	float bucketH = R * 0.12f;
	float bucketD = depth * 0.7f;
	for (int i = 0; i < numSpokes; i++) {
		float angle = (float)i * 360.0f / numSpokes;
		// Pegadas justo al aro exterior
		float px = R * 0.88f * cosf(glm::radians(angle));
		float py = R * 0.88f * sinf(glm::radians(angle));

		Bucket* bucket = new Bucket(bucketW, bucketH, bucketD, darkWoodMat);
		glm::mat4 pMat = glm::translate(glm::mat4(1.0f), glm::vec3(px, py, 0));
		// Rotar para que el lado abierto mire hacia el centro de la rueda
		pMat = glm::rotate(pMat, glm::radians(angle - 90.0f), glm::vec3(0, 0, 1));
		bucket->setModelMat(pMat);
		mWheel->addEntity(bucket);
	}
}

void WaterMill::update()
{
	mAngle += 1.5f;
	if (mAngle >= 360.0f) mAngle -= 360.0f;

	glm::mat4 rot = glm::rotate(glm::mat4(1.0f),
		glm::radians(-mAngle), glm::vec3(0, 0, 1));
	mWheel->setModelMat(rot);
}