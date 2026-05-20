#include "SnowMan.h"
#include "Sphere.h"
#include "Cone.h"
#include "Disk.h"
#include <glm/gtc/matrix_transform.hpp>


SnowMan::SnowMan(GLdouble radius)
{
	int muestras = 50;
	// Cuerpo
	Sphere* cuerpo = new Sphere(radius, muestras, muestras, Material(glm::vec4(0.95,0.95,0.95,1)));
	addEntity(cuerpo);
	// Cabeza
	Sphere* cabeza = new Sphere(radius*0.8, muestras, muestras, Material(glm::vec4(0.95, 0.95, 0.95, 1)));
	cabeza->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 1.8*radius, 0)));
	addEntity(cabeza);
	Cone* nariz = new Cone(radius, radius/4, 0, muestras, 20, Material(glm::vec4(1,0.65,0,1)));
	nariz->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 1.8*radius, radius/2)));
	nariz->setModelMat(glm::rotate(nariz->modelMat(), float(glm::radians(90.0f)), glm::vec3(1, 0, 0)));
	addEntity(nariz);
	// Ojos
	Cone* eye1 = new Cone(radius/3, radius / 4, 0, muestras, 20, Material(glm::vec4(0, 0.5, 0.5, 1)));
	eye1->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(radius / 6, 2.1 * radius, radius / 2)));
	eye1->setModelMat(glm::rotate(eye1->modelMat(), float(glm::radians(70.0f)), glm::vec3(1, 0, 0)));
	addEntity(eye1);
	Cone* eye2 = new Cone(radius/3, radius / 4, 0, muestras, 20, Material(glm::vec4(0, 0.5, 0.5, 1)));
	eye2->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(-radius / 6, 2.1 * radius, radius / 2)));
	eye2->setModelMat(glm::rotate(eye2->modelMat(), float(glm::radians(70.0f)), glm::vec3(1, 0, 0)));
	addEntity(eye2);
	// Sombrero
	sombrero = new CompoundEntity();
	addEntity(sombrero);
	// Disk
	Disk* bajoSombrero = new Disk(0, radius, radius, radius / 2, Material(glm::vec4(0, 1, 1, 1)));
	bajoSombrero->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 2.6 * radius, 0)));
	sombrero->addEntity(bajoSombrero);
	Disk* altoSombrero = new Disk(0, 0.8*radius, radius, radius / 2, Material(glm::vec4(1, 0, 0, 1)));
	altoSombrero->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 3 * radius, 0)));
	sombrero->addEntity(altoSombrero);
	Cone* cuerpoSombrero = new Cone(0.4*radius, radius*0.8, radius*0.8, muestras, muestras, Material(glm::vec4(0, 0, 1, 1)));
	cuerpoSombrero->setModelMat(glm::translate(glm::mat4(1.0), glm::vec3(0, 2.6 * radius, 0)));
	sombrero->addEntity(cuerpoSombrero);
}
