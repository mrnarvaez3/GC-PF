#ifndef H_Skybox_H
#define H_Skybox_H

#include "EntityWithTexture.h"

// Fondo de escena
class Skybox : public EntityWithTexture
{
public:
	Skybox(GLdouble size, Texture* texture, bool modulate);
	void render(const glm::mat4& modelViewMat) const override;
private:
	GLdouble mSize;
};

#endif //H_Skybox_H