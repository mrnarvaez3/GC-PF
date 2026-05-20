#include "../Entity.h"

class RGBCube : public EntityWithColors
{
public:
	RGBCube(GLdouble length);

	void update() override;
private:
	GLdouble length;
	bool init = false;
	double rot = 0;
};

