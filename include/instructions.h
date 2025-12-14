#ifndef GB_INST_H
#define GB_INST_H

#include "mmu.h"


void inc16(GB_CPU*, int);
void inc8(GB_CPU*, GB_MMU*, int);
void dec16(GB_CPU*, int);
void dec8(GB_CPU*, GB_MMU*, int);
void push(GB_CPU*, GB_MMU*, int);
void pop(GB_CPU*, GB_MMU*, int);
void bitwise_operations(GB_CPU*, GB_MMU*, int, char);
void ld_r2r(GB_CPU*, GB_MMU*, int, int);
void ld_n82r(GB_CPU*, GB_MMU*, int);
void ld_n162r16(GB_CPU*, GB_MMU*, int);
void ld_r82a16(GB_CPU*, GB_MMU*, int);
void ld_a162r8(GB_CPU*, GB_MMU*, int);

#endif
