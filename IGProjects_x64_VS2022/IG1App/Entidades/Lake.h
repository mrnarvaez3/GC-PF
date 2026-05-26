#ifndef H_Lake_H
#define H_Lake_H

#include "EntityWithTexture.h"

class Lake : public EntityWithTexture
{
public:
	Lake(	GLdouble R, GLuint nRings, GLuint nSamples, Texture* texture);
};


#endif //Mountain