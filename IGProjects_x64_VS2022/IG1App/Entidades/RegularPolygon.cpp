#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(GLuint num, GLdouble r, glm::vec4 nColor) : SingleColorEntity(nColor)
{
	mMesh = Mesh::generateRegularPolygon(num, r);
}