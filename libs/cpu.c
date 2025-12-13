#include "cpu.h"

void cpu_init(GB_CPU *cpu) {
    // 16-bit register pairs
    cpu->reg16[0] = &cpu->BC;   // BC
    cpu->reg16[1] = &cpu->DE;   // DE
    cpu->reg16[2] = &cpu->HL;   // HL
    cpu->reg16[3] = &cpu->SP;   // SP

    // 8-bit registers in Z80 order (B,C,D,E,H,L,(HL),A)
    cpu->reg8[0] = &cpu->B;
    cpu->reg8[1] = &cpu->C;
    cpu->reg8[2] = &cpu->D;
    cpu->reg8[3] = &cpu->E;
    cpu->reg8[4] = &cpu->H;
    cpu->reg8[5] = &cpu->L;
    cpu->reg8[6] = NULL;        // special: (HL)
    cpu->reg8[7] = &cpu->A;
}