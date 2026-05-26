#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>
#include "TextureManager.h"

#include "Light.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();

	//void render(Camera const& cam) const;
	virtual void render(Camera const& cam) const;
	virtual void update();

	virtual bool handleEvents(unsigned int key);

	// load or unload scene data into the GPU
	virtual void load();
	virtual void unload();

protected:
	void destroy();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gtObjects; // Entidades transparentes

	TextureManager* texManager = nullptr;

	std::vector<Light*> gLights;
	DirLight* dLight;
};

#endif //_H_Scene_H_
