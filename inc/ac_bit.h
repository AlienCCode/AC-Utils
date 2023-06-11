// Public domain (PD)

#ifndef _AC_BIT_H_
#define _AC_BIT_H_

#include "ac_types.h"

#define BIT_TST(n, b) ((n >> b) & 1)
#define BIT_SET(n, b) (n | (1 << b))
#define BIT_CLR(n, b) (n & ~(1 << b))
#define BIT_INV(n, b) (n ^ (1 << b))

extern UI64 BIT_LSB8(UI8 n);
extern UI64 BIT_LSB16(UI16 n);
extern UI64 BIT_LSB32(UI32 n);
extern UI64 BIT_LSB64(UI64 n);

extern UI64 BIT_MSB8(UI8 n);
extern UI64 BIT_MSB16(UI16 n);
extern UI64 BIT_MSB32(UI32 n);
extern UI64 BIT_MSB64(UI64 n);

#endif