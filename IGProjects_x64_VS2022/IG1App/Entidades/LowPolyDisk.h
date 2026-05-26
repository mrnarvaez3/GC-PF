#ifndef H_LowPolyDisk_H
#define H_LowPolyDisk_H

#include "LowPolyEntity.h"

class LowPolyDisk : public LowPolyEntity
{
public:
	LowPolyDisk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples, Material material);
};


#endif //H_LowPolyDisk_H