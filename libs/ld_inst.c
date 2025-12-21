#include "instructions.h"

/*
Implementations for all LD instructions
*/
void ld_r2r(GB_CPU *cpu, GB_MMU *mmu, int r1_register, int r2_register) {
    uint8_t value = r2_register == 6 ? bus_read(mmu, cpu->HL) : *cpu->reg8[r2_register];
    if (r1_register == 6)
        bus_write(mmu, cpu->HL, value);
    else
        *cpu->reg8[r1_register] = value;
    cpu->cpu_cycles++;
    cpu->machine_cycles += r2_register == 6 || r1_register == 6 ? 8 : 4;
}
void ld_n82r(GB_CPU *cpu, GB_MMU *mmu, int r1_register) {
    uint8_t value = bus_read(mmu, cpu->PC++);
    if (r1_register == 6)
        bus_write(mmu, cpu->HL, value);
    else
        *cpu->reg8[r1_register] = value;
    cpu->cpu_cycles += 2;
    cpu->machine_cycles += r1_register == 6 ? 12 : 8;
}
void ld_n162r16(GB_CPU *cpu, GB_MMU *mmu, int r1_register) {
    /*
    uint16_t bus_read16(GB_MMU *mmu, uint16_t address) {
        return (bus_read(mmu, address + 1) << 8) | bus_read(mmu, address);
    }
    */
    *cpu->reg16[r1_register] = bus_read16(mmu, cpu->PC);
    cpu->PC += 2; // increment PC after reading from memory
    cpu->cpu_cycles += 3;
    cpu->machine_cycles += 12;
}
void ld_r82a16(GB_CPU *cpu, GB_MMU *mmu, int r1_register) {
    if (r1_register == 2)
        bus_write(mmu, cpu->HL++, cpu->A);
    else if (r1_register == 3)
        bus_write(mmu, cpu->HL--, cpu->A);
    else
        bus_write(mmu, *cpu->reg16[r1_register], cpu->A);
    cpu->cpu_cycles++;
    cpu->machine_cycles += 8;
}
void ld_a162r8(GB_CPU *cpu, GB_MMU *mmu, int r1_register) {
    if (r1_register == 2)
        cpu->A = bus_read(mmu, cpu->HL++);
    else if (r1_register == 3)
        cpu->A = bus_read(mmu, cpu->HL--);
    else
        cpu->A = bus_read(mmu, *cpu->reg16[r1_register]);
    cpu->cpu_cycles++;
    cpu->machine_cycles += 8;
}