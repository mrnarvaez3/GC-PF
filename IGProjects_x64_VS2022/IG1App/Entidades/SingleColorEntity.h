#ifndef _H_SCE_H_
#define _H_SCE_H_

#include "../Entity.h"

// Apartado 3
class SingleColorEntity : public Abs_Entity
{
public:
	explicit SingleColorEntity(glm::vec4 color = glm::vec4(1, 1, 1, 1));
	void render(const glm::mat4& modelViewMat) const override;

	void setColor(glm::vec4 nColor);
	glm::vec4 getColor();
protected:
	glm::vec4 mColor;
};

#endif //_H_SCE_H_
