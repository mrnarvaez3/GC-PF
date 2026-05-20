#include "ColorMaterialEntity.h"

// Apartado 65
class Disk : public ColorMaterialEntity
{
public:
	Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, Material material = Material(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
};

