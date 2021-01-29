#pragma once
#include <stdint.h>



union MetaPosition {
	uint8_t position[4];
	uint32_t cache;
};
