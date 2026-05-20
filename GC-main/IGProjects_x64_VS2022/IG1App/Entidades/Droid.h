#include "CompoundEntity.h"

class Texture;
class SphereWithTexture;

// Apartado 68
class Droid : public CompoundEntity
{
public:
	Droid(GLdouble radius, Texture* texture);

	void update() override;

	void lightOnOff();

protected:
	SphereWithTexture* cuerpo = nullptr;
	CompoundEntity* cabeza = nullptr;

	SpotLight* spotLight;
};

