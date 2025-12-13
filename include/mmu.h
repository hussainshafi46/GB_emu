#ifndef GB_MMU_H
#define GB_MMU_H

#include "commons.h"

uint8_t bus_read(GB_MMU*, uint16_t);
uint16_t bus_read16(GB_MMU*, uint16_t);

uint8_t bus_write(GB_MMU*, uint16_t, uint8_t);
uint16_t bus_write16(GB_MMU*, uint16_t, uint8_t);

#endif
