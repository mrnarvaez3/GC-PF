#include "Scene5.h"
#include "../Entidades/Torus.h"

Scene5::~Scene5()
{
}

void Scene5::init()
{
	Scene::init();

	gObjects.push_back(new Torus(100, 30, 120, 120, Material(glm::vec4(0, 1, 0, 1))));
}
