#include "ColorMaterialEntity.h"

// Apartado 56
class Torus : public ColorMaterialEntity
{
public:
	Torus(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40, Material material = Material(glm::vec4(0.0f,1.0f,0.0f,1.0f)));
};

