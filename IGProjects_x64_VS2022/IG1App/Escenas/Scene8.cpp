#include "Scene8.h"
#include "../Entidades/Droid.h"
#include "../Entidades/Sphere.h"
#include "../Entidades/CompoundEntity.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Light.h"

void Scene8::init()
{
	Scene::init();

	posLightXY = new PosLight(0);
	posLightXY->setPosition(glm::vec3(0, 350, 0));
	gLights.push_back(posLightXY);

	spotLightYZ = new SpotLight(glm::vec3(0, 0, 250), 0);
	spotLightYZ->setCutoff(20,30);
	//spotLightYZ->setAttenuation();
	gLights.push_back(spotLightYZ);

	// Planeta
	gObjects.push_back(new Sphere(200, 200, 200, Material(glm::vec4(0.67, 0.13, 0.28, 1))));

	// Droid con nodo ficticio
	inventedNode = new CompoundEntity();
	droid = new Droid(20, texManager->getTexture("container.jpg", 1));
	inventedNode->addEntity(droid);
	droid->setModelMat(glm::translate(glm::mat4(1), { 0, 220, 0 }));
	gObjects.push_back(inventedNode);
}

void Scene8::load()
{
	Scene::load();
	glClearColor(0.0, 0.0, 0.0, 1.0); // background color negro
}

void Scene8::unload()
{
	Scene::unload();
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color se devuelve
}

bool Scene8::handleEvents(unsigned int key)
{
	Scene::handleEvents(key);
	// Apartado 70
	bool need_redisplay = true;
	switch (key) {
		case 'f':
			rotate();
			break;
		case 'g':
			orbit();
			break;
		case 't':
			posLightXY->setEnabled(!posLightXY->enabled());
			break;
		case 'y':
			spotLightYZ->setEnabled(!spotLightYZ->enabled());
			break;
		case 'h':
			droid->lightOnOff();
			break;
		need_redisplay = false;
	}
	return need_redisplay;
}

void Scene8::rotate()
{
	inventedNode->setModelMat(glm::rotate(inventedNode->modelMat(), float(glm::radians(3.0f)), { 0, 1, 0 }));
}

void Scene8::orbit()
{
	inventedNode->setModelMat(glm::rotate(inventedNode->modelMat(), float(glm::radians(3.0f)), { 1, 0, 0 }));
	// Rotacion eje X cuerpo
	inventedNode->update();
}


