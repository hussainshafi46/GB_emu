#include "instructions.h"

/*
Implementations for all PUSH instructions
*/
void push(GB_CPU* cpu, GB_MMU *mmu, int r_register) {
    uint16_t value = r_register == 3 ? cpu->AF : *cpu->reg16[r_register];
    uint8_t low = value & 0xFF;
    uint8_t high = (value >> 8) & 0xFF;
    
    // Stack grows downward
    bus_write(mmu, --cpu->SP, high);
    bus_write(mmu, --cpu->SP, low);

    cpu->cpu_cycles++;
    cpu->machine_cycles += 16;
}

/*
Implementations for all POP instructions
*/
void pop(GB_CPU* cpu, GB_MMU *mmu, int r_register) {
    uint8_t low = bus_read(mmu, cpu->SP++);
    uint8_t high = bus_read(mmu, cpu->SP++);
    

    if (r_register == 3) {
        // reg16[3] maps to SP **    
        // cpu->reg16[0] = &cpu->BC;
        // cpu->reg16[1] = &cpu->DE;
        // cpu->reg16[2] = &cpu->HL;
        // cpu->reg16[3] = &cpu->SP;
        // POP AF: lower 4 bits of F are always zero
        cpu->AF = ((high << 8) | low) & 0xFFF0;
    }
    else
        *cpu->reg16[r_register] = (high << 8) | low;

    cpu->cpu_cycles++;
    cpu->machine_cycles += 12;
}