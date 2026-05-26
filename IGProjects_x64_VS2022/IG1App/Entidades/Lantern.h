#ifndef H_Lantern_H
#define H_Lantern_H

#include "CompoundEntity.h"

// Objeto lampara
class Lantern : public CompoundEntity
{
public:
	Lantern(GLdouble size);
	void update() override;
	void lightOnOff();
	PosLight* getLight() const { return mLight; }

private:
	PosLight* mLight = nullptr;
	float mFlickerTime = 0.0f;
};

#endif //H_Lantern_H