#ifndef H_LowPolySphere_H
#define H_LowPolySphere_H

#include "LowPolyEntity.h"

class LowPolySphere : public LowPolyEntity
{
public:
	LowPolySphere(GLdouble radius, GLuint nP, GLuint nM, Material material);
};

#endif //H_LowPolySphere_H

