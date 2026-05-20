#ifndef _H_EntitiesWT_H_
#define _H_EntitiesWT_H_

#include "../Entity.h"
#include "../Texture.h"

// Apartado 19
class EntityWithTexture : public Abs_Entity
{
public:
	EntityWithTexture(Texture* texture, bool modulate);

	void render(const glm::mat4& modelViewMat) const override;
protected:
	Texture* mTexture;
	bool mModulate = false;
};

#endif //_H_EntitiesWT_H_

