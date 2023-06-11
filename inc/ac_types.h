// Public domain (PD)

#ifndef _AC_TYPES_H_
#define _AC_TYPES_H_

#include "ac_common.h"

#define VOID void

typedef int8_t   SI8;
typedef int16_t  SI16;
typedef int32_t  SI32;
typedef int64_t  SI64;
typedef uint8_t  UI8;
typedef uint16_t UI16;
typedef uint32_t UI32;
typedef uint64_t UI64;
typedef float    F32;
typedef double   F64;
typedef _Bool    BOOLEAN;
typedef char     CHAR;
typedef VOID    *VOIDPTR;

#undef NULL

#define SI8_MIN  -0x80
#define SI16_MIN -0x8000
#define SI32_MIN -0x80000000
#define SI64_MIN -0x8000000000000000
#define SI8_MAX   0x7F
#define SI16_MAX  0x7FFF
#define SI32_MAX  0x7FFFFFFF
#define SI64_MAX  0x7FFFFFFFFFFFFFFF
#define UI8_MAX   0xFF
#define UI16_MAX  0xFFFF
#define UI32_MAX  0xFFFFFFFF
#define UI64_MAX  0xFFFFFFFFFFFFFFFF

#define SI8_SIZE     (sizeof(SI8))
#define SI16_SIZE    (sizeof(SI16))
#define SI32_SIZE    (sizeof(SI32))
#define SI64_SIZE    (sizeof(SI64))
#define UI8_SIZE     (sizeof(UI8))
#define UI16_SIZE    (sizeof(UI16))
#define UI32_SIZE    (sizeof(UI32))
#define UI64_SIZE    (sizeof(UI64))
#define F32_SIZE     (sizeof(F32))
#define F64_SIZE     (sizeof(F64))
#define BOOLEAN_SIZE (sizeof(BOOLEAN))
#define CHAR_SIZE    (sizeof(CHAR))
#define VOIDPTR_SIZE (sizeof(VOIDPTR))

#define SI8_BITWIDTH     (SI8_SIZE << 3)
#define SI16_BITWIDTH    (SI16_SIZE << 3)
#define SI32_BITWIDTH    (SI32_SIZE << 3)
#define SI64_BITWIDTH    (SI64_SIZE << 3)
#define UI8_BITWIDTH     (UI8_SIZE << 3)
#define UI16_BITWIDTH    (UI16_SIZE << 3)
#define UI32_BITWIDTH    (UI32_SIZE << 3)
#define UI64_BITWIDTH    (UI64_SIZE << 3)
#define F32_BITWIDTH     (F32_SIZE << 3)
#define F64_BITWIDTH     (F64_SIZE << 3)
#define BOOLEAN_BITWIDTH 1
#define CHAR_BITWIDTH    (CHAR_SIZE << 3)
#define VOIDPTR_BITWIDTH (VOIDPTR_SIZE << 3)

#define FALSE          0
#define TRUE           1
#define NULL ((VOIDPTR)0)

#endif