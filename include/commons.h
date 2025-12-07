#ifndef GB_COMMONS_H
#define GB_COMMONS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define LOG_INFO(format, ...) fprintf(stdout, "[INFO] " format "\n", ##__VA_ARGS__)
#define LOG_ERROR(format, ...) fprintf(stderr, "[ERROR] %s:%d: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif