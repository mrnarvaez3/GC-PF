#include "ColorMaterialEntity.h"

// Apartado 65
class Cone : public ColorMaterialEntity
{
public:
	Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples, Material material = Material(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
};

