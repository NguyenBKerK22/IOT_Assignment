#include <Arduino.h>
#include "hal/modbus_uart.h"
#include "CRC16.h"
struct es_sm_thec_01_data {
  float temperature_value; // Temperature in Celsius
  float humidity_value; // Humidity in percentage
  float electrical_value; // Pressure in hPa
};
struct es_sm_thec_01 {
    uint8_t slave_address; // Slave address for the sensor
    uint8_t buffer[8]; // Buffer to hold the data
    es_sm_thec_01_data data; // Data structure to hold temperature, humidity, and pressure data
    CRC16 crc; // CRC object for error checking
    void readSensor() { // Function to read the sensor data
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
    float getTemperature() { // Function to get the temperature data
        return data.temperature_value; // Return the temperature value
    }
    float getHumidity() { // Function to get the humidity data
        return data.humidity_value; // Return the humidity value
    }
    float getPressure() { // Function to get the pressure data
        return data.electrical_value; // Return the pressure value
    }
};