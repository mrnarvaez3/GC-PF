#include "IndexedBox.h"
#include "../IndexMesh.h"

IndexedBox::IndexedBox(GLdouble l, Material material) : ColorMaterialEntity(material)
{
	mMesh = IndexMesh::generateIndexedBox(l);
}
