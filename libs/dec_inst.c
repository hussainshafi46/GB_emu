#include "instructions.h"

/*
Implementations for all DEC instructions
*/
void dec16(GB_CPU *cpu, int r_register) {
    (*cpu->reg16[r_register])--;
    cpu->cpu_cycles++;
    cpu->machine_cycles += 8;
}
void dec8(GB_CPU *cpu, GB_MMU *mmu, int r_register) {
    uint8_t old, result;
    
    cpu->cpu_cycles++;

    if (r_register == 6) {
        // (HL)
        old = bus_read(mmu, cpu->HL);
        result = old - 1;
        bus_write(mmu, cpu->HL, result);

        cpu->machine_cycles += 12;
    } else {
        old = *(cpu->reg8[r_register]);
        result = old - 1;
        *(cpu->reg8[r_register]) = result;

        cpu->machine_cycles += 4;
    }

    // flags
    uint8_t carry = cpu->F & FLAG_C;  // preserve C

    cpu->F = FLAG_N; // set N flag
    if (result == 0) cpu->F |= FLAG_Z;
    if ((old & 0x0F) == 0x00) cpu->F |= FLAG_H;
    cpu->F |= carry;
}
