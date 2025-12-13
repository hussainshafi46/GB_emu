#ifndef GB_COMMONS_H
#define GB_COMMONS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define LOG_INFO(format, ...) fprintf(stdout, "[INFO] " format "\n", ##__VA_ARGS__)
#define LOG_ERROR(format, ...) fprintf(stderr, "[ERROR] %s:%d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define HEADER_START 0x100 // starts at byte 256 (0x100)
#define HEADER_SIZE 0x50 // 80 bytes
typedef struct {
    uint8_t entrypoint[4];
    uint8_t nintendo_logo[48];
    uint8_t title[11];
    uint8_t manufacturer_code[4];
    uint8_t cgb_flag;
    uint8_t new_licensee_code[2];
    uint8_t sgb_flag;
    uint8_t cartridge_type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destination_code;
    uint8_t old_licensee_code;
    uint8_t mask_rom_version;
    uint8_t header_checksum;
    uint8_t global_checksum[2];
} GB_Cart;

#define FLAG_Z (1 << 7)
#define FLAG_N (1 << 6)
#define FLAG_H (1 << 5)
#define FLAG_C (1 << 4)
typedef struct {
    union {
        struct { uint8_t F, A; };
        uint16_t AF;
    };
    union {
        struct { uint8_t C, B; };
        uint16_t BC;
    };
    union {
        struct { uint8_t E, D; };
        uint16_t DE;
    };
    union {
        struct { uint8_t L, H; };
        uint16_t HL;
    };
    
    uint16_t SP;
    uint16_t PC;

    // Pointer tables
    uint16_t *reg16[4];  // BC, DE, HL, AF
    uint8_t  *reg8[8];   // B,C,D,E,H,L,(HL),A

    uint64_t cpu_cycles; // T-Cycles
    uint64_t machine_cycles; // M-Cycles

    bool is_halted;
    bool is_stopped;
    bool interrupt_master_enable;
} GB_CPU;

typedef struct {
} GB_PPU;
typedef struct {
} GB_MMU;

#endif