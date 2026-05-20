#include "Mesh.h"
#include <numbers>

// Apartado 54
class IndexMesh : public Mesh
{
public:
	virtual void draw() const override;
	virtual void load() override;
	virtual void unload() override;

	// Apartado 55
	static IndexMesh* generateByRevolution(
		const std::vector<glm::vec2>& profile, GLuint nSamples,
		GLfloat angleMax = 2 * std::numbers::pi);
	void buildNormalVectors();

	static IndexMesh* generateIndexedBox8(GLdouble l);
	static IndexMesh* generateIndexedBox(GLdouble l);
	static IndexMesh* generateSphere(GLdouble radius, GLuint nParallel, GLuint nMeridians);
private:
	std::vector<GLuint> vIndexes;
	GLuint mIBO;	
};

