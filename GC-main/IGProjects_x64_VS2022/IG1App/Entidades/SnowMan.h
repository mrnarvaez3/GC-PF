#include "CompoundEntity.h"

// Apartado 71
class SnowMan : public CompoundEntity
{
public:
	SnowMan(GLdouble radius);
protected:
	CompoundEntity* sombrero;
};

