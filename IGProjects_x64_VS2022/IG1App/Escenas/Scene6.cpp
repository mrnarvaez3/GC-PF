#include "Scene6.h"
#include "../Entidades/IndexedBox.h"

void Scene6::init()
{
	Scene::init();

	gObjects.push_back(new IndexedBox(100, Material(glm::vec4(0,1,0,1))));
}