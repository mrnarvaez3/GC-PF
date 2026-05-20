#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	dLight = new DirLight();
	dLight->setAmb({ 1,0,1 });
	dLight->setDirection(glm::vec3(-1.0f, -1.5f, -1.25f));
	// cambiar valores a los del shader parametrico
	gLights.push_back(dLight);

	texManager = new TextureManager();
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	for (Light* light : gLights)
		delete light;

	gLights.clear();

	for (Abs_Entity* el : gObjects)
		delete el;

	gObjects.clear();

	for (Abs_Entity* el : gtObjects)
		delete el;

	gtObjects.clear();

	texManager->destroy();

	delete(texManager);
}

void
Scene::load()
{
	for (Abs_Entity* obj : gObjects)
		obj->load();

	for (Abs_Entity* obj : gtObjects)
		obj->load();
}

void
Scene::unload()
{
	Shader* shader = Shader::get("light");
	shader->use();
	for (Light* light : gLights)
		light->unload(*shader);

	for (Abs_Entity* obj : gObjects)
		obj->unload();

	for (Abs_Entity* obj : gtObjects)
		obj->unload();
}

void
Scene::setGL()
{
	// OpenGL basic setting
	
	// Apartado 1, color fondo
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();
	 
	Shader* shader = Shader::get("light");
	shader->use();
	for (Light* light : gLights)
		light->upload(*shader, cam.viewMat());

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	// falta ordenar por distancia
	for (Abs_Entity* el : gtObjects)
		el->render(cam.viewMat());
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void Scene::update()
{
	for (Abs_Entity* el : gObjects)
		el->update();

	for (Abs_Entity* el : gtObjects)
		el->update();
}

bool Scene::handleEvents(unsigned int key)
{
	// Apartado 70
	bool need_redisplay = true;
	switch (key) {
	case 'r':
		dLight->setEnabled(!dLight->enabled());
		break;
	}
	return need_redisplay;
}
