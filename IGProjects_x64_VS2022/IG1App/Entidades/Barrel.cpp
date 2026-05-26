#include "Barrel.h"
#include "LowPolyEntity.h"
#include "LowPolyCone.h"
#include "LowPolyDisk.h"
#include "../IndexMesh.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

// Clase interna: cuerpo del barril (malla de revolucion)
class BarrelBody : public LowPolyEntity
{
public:
	BarrelBody(GLdouble height, GLdouble radius, Material material)
		: LowPolyEntity(material)
	{
		const int nPoints = 12;
		std::vector<glm::vec2> perfil(nPoints);

		for (int i = 0; i < nPoints; i++) {
			float t = (float)i / (float)(nPoints - 1);
			float y = (float)(height * t);
			float bulge = 1.0f + 0.2f * sinf(t * 3.14159265f);
			float r = (float)(radius * bulge);

			// Cerrar tapas con radio menor (no cero, dejamos espacio para el disco)
			if (i == 0 || i == nPoints - 1)
				r = (float)(radius * 0.85);

			perfil[i] = { r, y };
		}

		mMesh = IndexMesh::generateByRevolution(perfil, 10);
	}
};

Barrel::Barrel(GLdouble height, GLdouble radius, Material woodMat)
	: CompoundEntity()
{
	// Material metalico para las bandas
	Material metalMat(glm::vec3(0.4f, 0.4f, 0.45f));
	metalMat.setAmb({ 0.2f, 0.2f, 0.22f });
	metalMat.setDiff({ 0.4f, 0.4f, 0.45f });
	metalMat.setSpec({ 0.6f, 0.6f, 0.65f });
	metalMat.setExp(32.0f);

	// Cuerpo del barril 
	BarrelBody* body = new BarrelBody(height, radius, woodMat);
	addEntity(body);

	// Tapa superior (disco)
	LowPolyDisk* topCap = new LowPolyDisk(radius * 0.85, 0, 3, 10, woodMat);
	topCap->setModelMat(glm::translate(glm::mat4(1.0f),
		glm::vec3(0, (float)height, 0)));
	addEntity(topCap);

	// Tapa inferior (disco)
	LowPolyDisk* botCap = new LowPolyDisk(radius * 0.85, 0, 3, 10, woodMat);
	addEntity(botCap);

	// Bandas metalicas: anillos a distintas alturas
	// Usamos conos muy cortos y anchos como anillos
	float bandH = (float)(height * 0.09);  // grosor de la banda
	float positions[] = { 0.15f, 0.5f, 0.85f }; // posiciones relativas

	for (float pos : positions) {
		float y = (float)(height * pos);
		// Radio del barril a esa altura
		float bulge = 1.0f + 0.2f * sinf(pos * 3.14159265f);
		float r = (float)(radius * bulge) + 0.5f; // ligeramente por fuera

		LowPolyCone* band = new LowPolyCone(bandH, r, r, 3, 10, metalMat);
		band->setModelMat(glm::translate(glm::mat4(1.0f),
			glm::vec3(0, y - bandH / 2, 0)));
		addEntity(band);
	}
}