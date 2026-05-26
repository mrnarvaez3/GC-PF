#ifndef H_Barrel_H
#define H_Barrel_H

#include "CompoundEntity.h"
#include "../Material.h"

// Malla de revolucion (cuerpo) + tapas + bandas metalicas
class Barrel : public CompoundEntity
{
public:
	Barrel(GLdouble height, GLdouble radius, Material woodMat);
};

#endif //H_Barrel_H