#include "GlassParapet.h"

GlassParapet::GlassParapet(GLdouble length, Texture* texture, bool modulate) : EntityWithTexture(texture, modulate), length(length)
{
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}