#ifndef H_LowPolyCone_H
#define H_LowPolyCone_H

#include "LowPolyEntity.h"

class LowPolyCone : public LowPolyEntity
{
public:
	LowPolyCone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples, Material material);
};


#endif //H_LowPolyCone_H