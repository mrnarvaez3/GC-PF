#include "LowPolyBox.h"
#include "../IndexMesh.h"

LowPolyBox::LowPolyBox(GLdouble l, Material material)
	: LowPolyEntity(material)
{
	mMesh = IndexMesh::generateIndexedBox(l);
}