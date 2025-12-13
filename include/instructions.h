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

#endif
