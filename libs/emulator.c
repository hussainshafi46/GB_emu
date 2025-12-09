#include "emulator.h"
#include "utils.h"

int emu_start(const char* cartridge_file) {
    FILE *cart_file = fopen(cartridge_file, "rb");
    if (NULL == cart_file) {
        LOG_ERROR("Could not open cartridge file: %s", cartridge_file);
        return -1;
    }

    GB_Cart cart_header;
    read_cart_header(cart_file, &cart_header);

    fclose(cart_file);
    return 0;
}