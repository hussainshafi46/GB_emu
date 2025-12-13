#include "instructions.h"

/*
Implementations for all AND/OR/XOR instructions
*/
void bitwise_operations(GB_CPU *cpu, GB_MMU *mmu, int r_register, char operation) {
    uint8_t value = r_register == 6 ? bus_read(mmu, cpu->HL) : *cpu->reg8[r_register];

    cpu->F = 0; // clear all flags
    switch(operation) {
        case '&':
            cpu->A &= value;
            cpu->F = FLAG_H;
            break;
        case '|':
            cpu->A |= value;
            break;
        case '^':
            cpu->A ^= value;
            break;
        default: LOG_ERROR("Bad bitwise operator[%c]", operation);
    }
    if (!cpu->A) cpu->F |= FLAG_Z; // this should implicitly set/unset for 'AND A, A' and 'OR A, A'

    cpu->cpu_cycles++;
    cpu->machine_cycles += r_register == 6 ? 8 : 4;
}