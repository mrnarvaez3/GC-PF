#include "EntityWithTexture.h"

class SphereWithTexture : public EntityWithTexture
{
public:
	SphereWithTexture(GLdouble radius, GLuint nParallel, GLuint nMeridians, Texture* texture, bool modulate);
};

