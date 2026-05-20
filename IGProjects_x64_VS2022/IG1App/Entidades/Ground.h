#include "EntityWithTexture.h"

// Apartado 21
class Ground : public EntityWithTexture
{
public:
	Ground(GLdouble w, GLdouble h, Texture* texture, bool modulate);
};

