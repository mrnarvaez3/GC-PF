#ifndef _H_CEntities_H_
#define _H_CEntities_H_

#include "../Entity.h"

// Apartado 66
class CompoundEntity : public Abs_Entity
{
public:
	CompoundEntity();
	~CompoundEntity();

	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

	void load() override;
	void unload() override;

	void addEntity(Abs_Entity* ae);
protected:
	std::vector<Abs_Entity*> gObjects;
};

#endif //_H_CEntities_H_
