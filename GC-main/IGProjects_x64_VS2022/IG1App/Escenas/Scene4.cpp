#include "Scene4.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../Entidades/Ground.h"
#include "../Texture.h"
#include "../Entidades/BoxOutline.h"
#include "../Entidades/Star3D.h"
#include "../Entidades/Box.h"
#include "../Entidades/GlassParapet.h"
#include "../Entidades/Grass.h"
#include "../Entidades/Photo.h"

Scene4::~Scene4()
{
	delete(photoTex);
}

void Scene4::init()
{
	Scene::init();
		
	photoTex = new Texture();
	photoTex->loadColorBuffer(800,600);
	
	//gObjects.push_back(new BoxOutline(160, texManager->getTexture("papelE.png", 1), texManager->getTexture("papelE.png", 1), false));
	gObjects.push_back(new Ground(320, 320, texManager->getTexture("baldosaC.png", 1), false));
	gObjects.push_back(new Box(80, texManager->getTexture("papelE.png", 1), texManager->getTexture("container.jpg", 1), false));
	gObjects[2]->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(75, 80, -75)));
	gObjects.push_back(new Star3D(30, 8, 20, texManager->getTexture("rueda.png", 1)));
	gObjects[3]->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(75, 80, -75)));
	photo = new Photo(120, 120, photoTex, false);
	gObjects.push_back(photo);
	gObjects[4]->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 10, 0)));
	gObjects[4]->setModelMat(glm::rotate(gObjects[4]->modelMat(), float(glm::radians(-90.0f)), glm::vec3(1, 0, 0)));
	gtObjects.push_back(new GlassParapet(320, texManager->getTexture("windowC.png", 200), false));
	gtObjects[0]->setModelMat(glm::scale(glm::mat4(1.0), glm::vec3(1,0.25f,1)));
	gObjects.push_back(new Grass(50, 50, texManager->getTexture("grass.png", 255), false));
	gObjects[5]->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(100,25,-100)));
}

void Scene4::photoUpdate()
{
	photo->update();
}

