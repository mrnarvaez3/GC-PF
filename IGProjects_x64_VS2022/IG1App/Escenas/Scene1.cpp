#include "Scene1.h"
#include "../Entidades/RegularPolygon.h"

void Scene1::init()
{
	Scene::init();
	// Apartado 5
	// Hexagono
	gObjects.push_back(new RegularPolygon(6, 80, glm::vec4(1.0, 0.0, 1.0, 1.0)));
	// Circunferencia
	gObjects.push_back(new RegularPolygon(50, 80, glm::vec4(1.0, 1.0, 0, 1.0)));
}