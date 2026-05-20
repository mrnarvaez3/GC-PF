#include "Scene10.h"
#include "../Material.h"
#include "../Entidades/Sphere.h"
#include <glm/gtc/matrix_transform.hpp>

void Scene10::init()
{
	Scene::init();
	Abs_Entity* ent;
	Material mat = Material(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
	mat.setGolden();
	ent = new Sphere(50, 50, 50, mat);
	gObjects.push_back(ent);
	ent->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 0, 200)));

	ent = new Sphere(50, 50, 50, Material(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)));
	gObjects.push_back(ent);
	ent->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(200, 0, 0)));
}
