#include "EntityWithTexture.h"

// Apartado 32
class GlassParapet : public EntityWithTexture
{
public:
	GlassParapet(GLdouble length, Texture* tex, bool modulate);
private:
	GLdouble length;
};

