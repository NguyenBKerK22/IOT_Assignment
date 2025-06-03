#include "utils.h"
#include "CRC16.h" // Include the CRC16 library for CRC calculations
uint16_t calculateCRC(uint8_t *data, size_t length) { // Function to calculate CRC
    CRC16 crc; // Create a CRC16 object
    crc.add((uint8_t *) data, length); // Initial CRC value
    return crc.getCRC(); // Get the CRC value
}