#include "SingleColorEntity.h"

class Cube : public SingleColorEntity
{
public:
	Cube(GLdouble length);

	void render(const glm::mat4& modelViewMat) const override;
};

