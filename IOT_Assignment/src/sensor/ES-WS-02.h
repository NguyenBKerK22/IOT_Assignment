#include <Arduino.h>
#include "hal/modbus_uart.h"
#include "CRC16.h"
struct es_ws_02_data {
    int windSpeed; // Wind speed in m/s
};
struct es_ws_02 {
    uint8_t slave_address; // Slave address for the sensor
    uint8_t buffer[8];
    es_ws_02_data data; // Data structure to hold wind speed data
    CRC16 crc; // CRC object for error checking
    void readSensor() { // Function to read the sensor data // Buffer to hold the data
        buffer[0] = 0x01; // Slave address
        buffer[1] = 0x03; // Function code for reading holding registers
        buffer[2] = 0x00; // Starting address high byte
        buffer[3] = 0x00; // Starting address low byte
        buffer[4] = 0x00; // Number of registers high byte
        buffer[5] = 0x01; // Number of registers low byte
        // Calculate CRC (Cyclic Redundancy Check) for error checking
        crc.add((uint8_t *) buffer, 6); // Initial CRC value
        uint16_t crc_result = crc.getCRC(); // Get the CRC value
        buffer[6] = crc_result >> 8; // CRC high byte
        buffer[7] = crc_result & 0xFF; // CRC low byte
    }
    void setSlaveAddress(uint8_t address) { // Function to set the slave address
        slave_address = address; // Set the slave address
        buffer[0] = slave_address; // Slave address
        buffer[1] = 0x10; // Function code for reading holding registers
        buffer[2] = 0x00; // Starting address high byte
        buffer[3] = 0x00; // Starting address low byte
        buffer[4] = 0x00; // Number of registers high byte
        buffer[5] = 0x01; // Number of registers low byte
        // Calculate CRC (Cyclic Redundancy Check) for error checking
        crc.add((uint8_t *) buffer, 6); // Initial CRC value
        uint16_t crc_result = crc.getCRC(); // Get the CRC value
        buffer[6] = crc_result >> 8; // CRC high byte
        buffer[7] = crc_result & 0xFF; // CRC low byte
    }
    int getWindSpeed() { // Function to get the wind speed data
        return data.windSpeed; // Return the wind speed value
    }
};