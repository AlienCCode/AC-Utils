// Public domain (PD)

#ifndef _AC_MATH_H_
#define _AC_MATH_H_

#include "ac_bit.h"

#define PI     3.1415926535897932384626433832795028841971693993751058209749445L
#define TAU    (PI * 2.0f)
#define EULER  2.71828182845904523536028747135266249775724709369995
#define SQRT_2 1.41421356237309504880
#define PHI    1.61803398874989484820

extern UI64 SeedIter;

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
#define CLAMP(n, a, b) \
(n < MIN(a, b) ? MIN(a, b) : n > MAX(a, b) ? MAX(a, b) : n)
#define ABS(n) (n < 0 ? -n : n)
#define DEG2RAD(n) (n / 180.0f * PI)
#define RAD2DEG(n) (n / PI * 180.0f)

// Sets the seed for RAND
// \param seed The seed to initialize to.
extern VOID SEED(UI64 seed);

// Generates a random number
// \return A random number between 0 and UI64_MAX.
extern UI64 RAND(VOID);

#endif