#include "EntityWithTexture.h"

// Apartado 24
class BoxOutline : public EntityWithTexture
{
public:
	BoxOutline(GLdouble length, Texture* tex, Texture* tex2, bool modulate);

	void render(const glm::mat4& modelViewMat) const override;

private:
	GLdouble length;
	Texture* mTexture2;
};

