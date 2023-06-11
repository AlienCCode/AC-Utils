// Public domain (PD)

#include "ac_bit.h"

UI64 BIT_LSB8(UI8 n) {
	UI64 i = 0;
	while (!(n & 1) && i < UI8_BITWIDTH) {
		n >>= 1;
	}
	return i != UI8_BITWIDTH ? i : UI64_MAX;
}

UI64 BIT_LSB16(UI16 n) {
	UI64 i = 0;
	while (!(n & 1) && i < (UI16_BITWIDTH << 3)) {
		n >>= 1; ++i;
	}
	return i != UI16_BITWIDTH ? i : UI64_MAX;
}

UI64 BIT_LSB32(UI32 n) {
	UI64 i = 0;
	while (!(n & 1) && i < (UI32_BITWIDTH << 3)) {
		n >>= 1; ++i;
	}
	return i != UI32_BITWIDTH ? i : UI64_MAX;
}

UI64 BIT_LSB64(UI64 n) {
	UI64 i = 0;
	while (!(n & 1) && i < (UI64_BITWIDTH << 3)) {
		n >>= 1; ++i;
	}
	return i != UI64_BITWIDTH ? i : UI64_MAX;
}

UI64 BIT_MSB8(UI8 n) {
	UI64 i = UI8_BITWIDTH;
	while (--i && !(n & SI8_MIN)) {
		n <<= 1; ++i;
	}
	return i != 0 ? i : UI64_MAX;
}

UI64 BIT_MSB16(UI16 n) {
	UI64 i = UI16_BITWIDTH;
	while (--i && !(n & SI16_MIN)) {
		n <<= 1;
	}
	return i != 0 ? i : UI64_MAX;
}

UI64 BIT_MSB32(UI32 n) {
	UI64 i = UI32_BITWIDTH;
	while (--i && !(n & SI32_MIN)) {
		n <<= 1;
	}
	return i != 0 ? i : UI64_MAX;
}

UI64 BIT_MSB64(UI64 n) {
	UI64 i = UI64_BITWIDTH;
	while (--i && !(n & SI64_MIN)) {
		n <<= 1;
	}
	return i != 0 ? i : UI64_MAX;
}