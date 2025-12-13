#ifndef GB_UTILS_H
#define GB_UTILS_H

#include "mmu.h"


void read_cart_header(FILE*, GB_Cart*);
void cpu_step(GB_CPU*, GB_MMU*);
#endif
