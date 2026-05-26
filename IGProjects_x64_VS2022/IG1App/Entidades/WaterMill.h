#ifndef H_WaterMill_H#ifndef H_WaterMill_H
#define H_WaterMill_H

#include "CompoundEntity.h"

// Entidad compuesta + Animacion
class WaterMill : public CompoundEntity
{
public:
	WaterMill(GLdouble radius);
	void update() override;

private:
	CompoundEntity* mWheel = nullptr;
	float mAngle = 0.0f;
};

#endif //H_WaterMill_H