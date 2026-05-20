#include "Scene7.h"
#include "../Entidades/Sphere.h"
#include "../Entidades/Disk.h"
#include "../Entidades/Cone.h"
#include "../Entidades/SphereWithTexture.h"
#include "../Entidades/CompoundEntity.h"
#include "../Entidades/Droid.h"

void Scene7::init()
{
	Scene::init();

	//gObjects.push_back(new Sphere(50, 50, 50));
	//gObjects.push_back(new SphereWithTexture(50, 50, 50, texManager->getTexture("container.jpg", 1), false));
	//gObjects.push_back(new Disk(100, 50, 50, 50));
	//gObjects.push_back(new Cone(100, 60, 20, 20, 20));
	gObjects.push_back(new Droid(50, texManager->getTexture("container.jpg", 1)));

}
