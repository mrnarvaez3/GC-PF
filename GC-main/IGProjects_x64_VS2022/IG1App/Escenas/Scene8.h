#include "../Scene.h"

class CompoundEntity;
class Droid;

// Apartado 69
class Scene8 : public Scene
{
public:
	void init() override;

	void load() override;
	void unload() override;

	bool handleEvents(unsigned int key) override;

	void rotate();
	void orbit();

private:
	Droid* droid;

	CompoundEntity* inventedNode;
	PosLight* posLightXY;
	SpotLight* spotLightYZ;
};

