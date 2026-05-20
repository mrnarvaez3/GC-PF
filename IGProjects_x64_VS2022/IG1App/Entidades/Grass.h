#include "EntityWithTexture.h"

// Apartado 33
class Grass : public EntityWithTexture
{
public:
	Grass(GLdouble w, GLdouble h, Texture* texture, bool modulate);
	void render(const glm::mat4& modelViewMat) const override;
};

