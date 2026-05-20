#include "../Scene.h"

class Texture;
class Photo;

// Apartado 37
class Scene4 : public Scene
{
public:
	~Scene4();
	void init() override;

	void photoUpdate();

private:
	Texture* photoTex = nullptr;
	Photo* photo = nullptr;
};

