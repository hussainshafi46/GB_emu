#include "mmu.h"

uint8_t bus_read(GB_MMU *mmu, uint16_t address) {
    // TODO
    return 0L;
}
uint16_t bus_read16(GB_MMU *mmu, uint16_t address) {
    return (bus_read(mmu, address + 1) << 8) | bus_read(mmu, address);
}