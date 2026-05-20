#include "../Entity.h"

class RGBTriangle : public EntityWithColors
{
public:
	RGBTriangle(GLdouble r);
	void update() override;
private:
	double rot;
	bool init = false;
};


