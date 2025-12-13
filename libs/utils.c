#include "utils.h"

void read_cart_header(FILE *cart_file, GB_Cart *header) {
    size_t read;

    if (NULL == header) {
        LOG_ERROR("Header struct is NULL");
        return;
    }

    if (fseek(cart_file, HEADER_START, SEEK_SET) != 0) {
        LOG_ERROR("Failed to seek to cartridge header");
        return;
    }

    read = fread(header, 1, HEADER_SIZE, cart_file);
    if (read < HEADER_SIZE) {
        LOG_ERROR("Failed to read cartridge header");
        return;
    }

    LOG_INFO("Read cartridge header for: '%s' successfully", header->title);
}

void cpu_step(GB_CPU *cpu, GB_MMU *mmu) {
    uint8_t opcode;
    int row, col, r_register;
    
    opcode = bus_read(mmu, cpu->PC);

    switch(opcode) {
        case 0x00: break; // NOP
        case 0x10: break; // STOP
        case 0x76: break; // HALT
        case 0xCB: break; // prefixed
        case 0xF3: break; // DI
        case 0xFB: break; // EI

        // INC
        case 0x04: case 0x0C:
        case 0x14: case 0x1C:
        case 0x24: case 0x2C:
        case 0x34: case 0x3C: {
            r_register = (opcode >> 3) & 7;
            inc8(cpu, mmu, r_register);
            break;
        }
        case 0x03: case 0x13:
        case 0x23: case 0x33: {
            r_register = (opcode >> 4) & 3;
            inc16(cpu, r_register);
            break;
        }

        // DEC
        case 0x05: case 0x0D:
        case 0x15: case 0x1D:
        case 0x25: case 0x2D:
        case 0x35: case 0x3D: {
            r_register = (opcode >> 3) & 7;
            dec8(cpu, mmu, r_register);
            break;
        }
        case 0x0B: case 0x1B:
        case 0x2B: case 0x3B: {
            r_register = (opcode >> 4) & 3;
            dec16(cpu, r_register);
            break;
        }

        default:
         // TODO: if-else ladder to group instructions
            // row = ((opcode & 0xF0) >> 1);
            // col = (opcode & 0x0F);
            // if (col == 3 && row < 4) {
            //     inc16(cpu, row);
            // }
            // else if (row < 4 && (col == 4 || col == 0xC)) {
            //     inc8(cpu, row, col);
            // }
    }

}