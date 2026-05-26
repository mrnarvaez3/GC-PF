#ifndef H_Bench_H
#define H_Bench_H

#include "LowPolyEntity.h"

// Malla indexada manual banca
class Bench : public LowPolyEntity
{
public:
	Bench(GLdouble length, Material material);
};

#endif //H_Bench_H