#include "EntityWithTexture.h"

// Apartado 30
class Box : public EntityWithTexture
{
public:
	Box(GLdouble length, Texture* tex, Texture* tex2, bool modulate);
	~Box();

	void render(const glm::mat4& modelViewMat) const override;
	void update();

	void setModelMat(glm::mat4 const& aMat);
private:
	float fac = 4;
	float alt = 0;
	float rot = 0;
	bool up = true;

	GLdouble length;
	Texture* mTexture2;
	glm::mat4 aMat1 = glm::mat4(1.0);
	glm::mat4 aMat2 = glm::mat4(1.0);
	Mesh* mMesh1;
	Mesh* mMesh2;
};

