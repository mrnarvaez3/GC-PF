#include "Scene9.h"
#include "../Entidades/SnowMan.h"

void Scene9::init()
{
	Scene::init();
	gObjects.push_back(new SnowMan(50));
}
