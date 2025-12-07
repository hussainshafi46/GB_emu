#include "emulator.h"

int main(int argc, char** argv) {
    if (2 != argc) {
        LOG_ERROR("USAGE: %s <ROM FILE>", argv[0]);
        return -1;
    }
    return 0;
}