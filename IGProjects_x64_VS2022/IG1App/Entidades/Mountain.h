#ifndef H_Mountain_H
#define H_Mountain_H

#include "EntityWithTexture.h"

class Mountain : public EntityWithTexture
{
public:
	Mountain(GLdouble h, GLdouble r, GLdouble R, GLuint nRings, GLuint nSamples, Texture* texture);
};


#endif //Mountain