#include "Scene3.h"
#include "../Entidades/Cube.h"
#include "../Entidades/RGBCube.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene3::init()
{
	Scene::init();

	//gObjects.push_back(new Cube(80));
	gObjects.push_back(new RGBCube(80));
}
