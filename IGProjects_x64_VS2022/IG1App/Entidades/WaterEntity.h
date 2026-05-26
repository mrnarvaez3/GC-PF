#ifndef H_WaterEntity_H
#define H_WaterEntity_H

#include "LowPolyEntity.h"

class WaterEntity : public LowPolyEntity
{
public:
	WaterEntity(GLdouble width, GLdouble depth, GLuint subdivs, Material material);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

private:
	float mTime = 0.0f;
	float mAmplitude = 1.5f;
	float mFrequency = 0.04f;
};


#endif //H_WaterEntity_H