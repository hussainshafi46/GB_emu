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
    int row, col, r1_register, r2_register;
    
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
            r1_register = (opcode >> 3) & 7;
            inc8(cpu, mmu, r1_register);
            break;
        }
        case 0x03: case 0x13:
        case 0x23: case 0x33: {
            r1_register = (opcode >> 4) & 3;
            inc16(cpu, r1_register);
            break;
        }

        // DEC
        case 0x05: case 0x0D:
        case 0x15: case 0x1D:
        case 0x25: case 0x2D:
        case 0x35: case 0x3D: {
            r1_register = (opcode >> 3) & 7;
            dec8(cpu, mmu, r1_register);
            break;
        }
        case 0x0B: case 0x1B:
        case 0x2B: case 0x3B: {
            r1_register = (opcode >> 4) & 3;
            dec16(cpu, r1_register);
            break;
        }

        // PUSH
        case 0xC5: case 0xD5:
        case 0xE5: case 0xF5: {
            r1_register = (opcode >> 4) & 3;
            push(cpu, mmu, r1_register);
            break;
        }

        // POP
        case 0xC1: case 0xD1:
        case 0xE1: case 0xF1: {
            r1_register = (opcode >> 4) & 3;
            pop(cpu, mmu, r1_register);
            break;
        }

        // AND
        case 0xA0: case 0xA1:
        case 0xA2: case 0xA3:
        case 0xA4: case 0xA5:
        case 0xA6: case 0xA7: {
            r1_register = opcode & 7;
            bitwise_operations(cpu, mmu, r1_register, '&');
            break;
        }

        // OR
        case 0xB0: case 0xB1:
        case 0xB2: case 0xB3:
        case 0xB4: case 0xB5:
        case 0xB6: case 0xB7: {
            r1_register = opcode & 7;
            bitwise_operations(cpu, mmu, r1_register, '|');
            break;
        }

        // XOR
        case 0xA8: case 0xA9:
        case 0xAA: case 0xAB:
        case 0xAC: case 0xAD:
        case 0xAE: case 0xAF: {
            r1_register = opcode & 7;
            bitwise_operations(cpu, mmu, r1_register, '^');
            break;
        }

        // LD
        case 0x40: case 0x41: case 0x42: case 0x43:
        case 0x44: case 0x45: case 0x46: case 0x47:
        case 0x48: case 0x49: case 0x4A: case 0x4B:
        case 0x4C: case 0x4D: case 0x4E: case 0x4F:
        case 0x50: case 0x51: case 0x52: case 0x53:
        case 0x54: case 0x55: case 0x56: case 0x57:
        case 0x58: case 0x59: case 0x5A: case 0x5B:
        case 0x5C: case 0x5D: case 0x5E: case 0x5F:
        case 0x60: case 0x61: case 0x62: case 0x63:
        case 0x64: case 0x65: case 0x66: case 0x67:
        case 0x68: case 0x69: case 0x6A: case 0x6B:
        case 0x6C: case 0x6D: case 0x6E: case 0x6F:
        case 0x70: case 0x71: case 0x72: case 0x73:
        case 0x74: case 0x75: case 0x77: // 0x76 is HALT
        case 0x78: case 0x79: case 0x7A: case 0x7B:
        case 0x7C: case 0x7D: case 0x7E: case 0x7F: {
            r1_register = (opcode >> 3) & 7;
            r2_register = opcode & 7;
            ld_r2r(cpu, mmu, r1_register, r2_register);
            break;
        }
        case 0x06: case 0x16:
        case 0x26: case 0x36:
        case 0x0E: case 0x1E:
        case 0x2E: case 0x3E: {
            r1_register = (opcode >> 3) & 7;
            ld_n82r(cpu, mmu, r1_register);
            break;
        }
        case 0x01: case 0x11:
        case 0x21: case 0x31: {
            r1_register = (opcode >> 4) & 3;
            ld_n162r16(cpu, mmu, r1_register);
            break;
        }
        case 0x02: case 0x12:
        case 0x22: case 0x32: {
            r1_register = (opcode >> 4) & 3;
            ld_r82a16(cpu, mmu, r1_register);
            break;
        }
        case 0x0A: case 0x1A:
        case 0x2A: case 0x3A: {
            r1_register = (opcode >> 4) & 3;
            ld_a162r8(cpu, mmu, r1_register);
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