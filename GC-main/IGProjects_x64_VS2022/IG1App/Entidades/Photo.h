#include "EntityWithTexture.h"

// Apartado 35
class Photo : public EntityWithTexture
{
public:
	Photo(GLdouble w, GLdouble h, Texture* texture, bool modulate);
	void update();
private:
	double w = 0;
	double h = 0;
};

