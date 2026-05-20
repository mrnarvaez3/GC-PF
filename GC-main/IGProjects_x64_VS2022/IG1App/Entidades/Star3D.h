#include "SingleColorEntity.h"
#include "EntityWithTexture.h"

class Star3D : public EntityWithTexture
{
public:
	Star3D(GLdouble re, GLuint np, GLdouble h, Texture* tex);

	void render(const glm::mat4& modelViewMat) const override;
	void update();

	void setModelMat(glm::mat4 const& aMat);
protected:
	float rot = 0;
	glm::mat4 aMat2 = glm::mat4(1.0);
	glm::mat4 baseMat = glm::mat4(1.0);
};

