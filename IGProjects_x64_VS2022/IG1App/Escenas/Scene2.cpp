#include "Scene2.h"
#include "../Entidades/RGBTriangle.h"
#include "../Entidades/RGBRectangle.h"
#include "../Entidades/RegularPolygon.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene2::init()
{
	Scene::init();

	// Apartado 10
	gObjects.push_back(new RGBRectangle(80*glm::sqrt(2), 80 * glm::sqrt(2)));
	gObjects.push_back(new RegularPolygon(50, 80, glm::vec4(1.0, 0.0, 1.0, 1.0)));
	gObjects.push_back(new RGBTriangle(40));
}

