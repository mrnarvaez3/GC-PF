#include "Droid.h"
#include "Cone.h"
#include "Disk.h"
#include "SphereWithTexture.h"
#include "../TextureManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Texture.h"

Droid::Droid(GLdouble radius, Texture* texture) : CompoundEntity()
{
	spotLight = new SpotLight(glm::vec3(0, 0, 0), 1);
	spotLight->setCutoff(40, 50);
	spotLight->setDirection(glm::vec3(0, -1, 0));
	gLights.push_back(spotLight);

	int muestras = 50;
	// Cuerpo
	cuerpo = new SphereWithTexture(radius, muestras, muestras, texture, false);
	addEntity(cuerpo);
	// Cabeza
	cabeza = new CompoundEntity();
	addEntity(cabeza);
	// Cono cabeza
	Cone* cone = new Cone(radius / 2, radius, radius / 2, muestras, muestras, Material(glm::vec4(1, 1, 0, 1)));
	cone->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, radius, 0)));
	cabeza->addEntity(cone);
	// Disco tapa
	Disk* disk = new Disk(0, radius / 2, radius / 2, muestras, Material(glm::vec4(1, 1, 0, 1)));
	disk->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 1.5*radius, 0)));
	cabeza->addEntity(disk);
	// Ojos
	Cone* eye1 = new Cone(radius, radius / 8, radius / 8, muestras, muestras, Material(glm::vec4(0, 0.8, 0, 1)));
	eye1->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(radius / 8, 1.25 *radius, radius/2)));
	eye1->setModelMat(glm::rotate(eye1->modelMat(), float(glm::radians(90.0f)), glm::vec3(1, 0, 0)));
	cabeza->addEntity(eye1);
	Cone* eye2 = new Cone(radius, radius/8, radius / 8, muestras, muestras, Material(glm::vec4(0, 0.8, 0, 1)));
	eye2->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(-radius / 8, 1.25 * radius, radius/2)));
	eye2->setModelMat(glm::rotate(eye2->modelMat(), float(glm::radians(90.0f)), glm::vec3(1, 0, 0)));
	cabeza->addEntity(eye2);
}

void Droid::update()
{
	// Movimiento del cuerpo
	if (cuerpo != nullptr) {
		// Rotacion sobre su eje X
		cuerpo->setModelMat(glm::rotate(cuerpo->modelMat(), float(glm::radians(3.0f)), glm::vec3(1, 0, 0)));
	}
}

void Droid::lightOnOff()
{
	spotLight->setEnabled(!spotLight->enabled());
}
