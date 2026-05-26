#include "Bench.h"
#include "../IndexMesh.h"

Bench::Bench(GLdouble length, Material material) : LowPolyEntity(material)
{
	mMesh = IndexMesh::generateBench(length);
}