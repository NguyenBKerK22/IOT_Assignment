#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>  // Cho size_t

#ifdef __cplusplus
extern "C" {
#endif

uint16_t calculateCRC(uint8_t *data, size_t length);

#ifdef __cplusplus
}
#endif

#endif // UTILS_H