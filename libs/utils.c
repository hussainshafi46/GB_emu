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