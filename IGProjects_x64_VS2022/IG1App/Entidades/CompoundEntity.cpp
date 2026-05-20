#include "CompoundEntity.h"

CompoundEntity::CompoundEntity() : Abs_Entity()
{
}

CompoundEntity::~CompoundEntity()
{
	for (Light* light : gLights)
		delete light;

	for (Abs_Entity* el : gObjects)
		delete el;

	gLights.clear();
	gObjects.clear();
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const
{
	glm::mat4 aMat = modelViewMat * mModelMat;

	Shader* shader = Shader::get("light");
	shader->use();
	for (Light* light : gLights)
		light->upload(*shader, aMat);

	for (Abs_Entity* el : gObjects)
		el->render(aMat);
}

void CompoundEntity::update()
{
	for (Abs_Entity* el : gObjects)
		el->update();
}

void CompoundEntity::load()
{
	for (Abs_Entity* el : gObjects)
		el->load();
}

void CompoundEntity::unload()
{
	Shader* shader = Shader::get("light");
	shader->use();
	for (Light* light : gLights)
		light->unload(*shader);

	for (Abs_Entity* el : gObjects)
		el->unload();
}

void CompoundEntity::addEntity(Abs_Entity* ae)
{
	gObjects.push_back(ae);
}
