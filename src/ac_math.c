#include "ac_math.h"

UI64 SeedIter = 0;

VOID SEED(UI64 seed) {
	SeedIter = seed;
}

UI64 RAND(VOID) {
	UI64 const A = 583078956743489351, B = 81439;
	return SeedIter = A * SeedIter + B;
}