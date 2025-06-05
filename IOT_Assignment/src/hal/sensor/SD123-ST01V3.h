#include <Arduino.h>
#include "hal/modbus_uart.h"
#include "hal/modbus_queue.h"
#include "hal/crc.h"
struct sd123_st01v3_data {
  float temperature_value; // Temperature in Celsius
  float humidity_value; // Humidity in percentage
};
struct sd123_st01v3 {
    uint8_t slave_address; // Slave address for the sensor
    uint8_t tx_buffer[8]; // Buffer to hold the data
    uint8_t rx_buffer[256]; // Buffer to hold the data
    sd123_st01v3_data data; // Data structure to hold temperature, humidity, and pressure data
    sd123_st01v3(uint8_t address) : slave_address(address) { // Constructor to initialize the slave address
        memset(tx_buffer, 0, sizeof(tx_buffer)); // Initialize tx_buffer to zero
        memset(rx_buffer, 0, sizeof(rx_buffer)); // Initialize rx_buffer to zero
    }
    void prepareBuffer() { // Function to prepare the Modbus request buffer
        // tx_buffer to hold the data
        tx_buffer[0] = slave_address; // Slave address
        tx_buffer[1] = 0x03; // Function code for reading holding registers
        tx_buffer[2] = 0x02; // Starting address high byte
        tx_buffer[3] = 0x00; // Starting address low byte
        tx_buffer[4] = 0x00; // Number of registers high byte
        tx_buffer[5] = 0x02; // Number of registers low byte
        // Calculate CRC (Cyclic Redundancy Check) for error checking
        uint16_t crc_result = crc16(tx_buffer, 6); // Calculate CRC for the first 6 bytes
        tx_buffer[7] = crc_result >> 8; // CRC high byte
        tx_buffer[6] = crc_result & 0xFF; // CRC low byte
    }
    void parseData(uint8_t* buffer, uint8_t* id, uint8_t* func, uint8_t* byte_num, uint8_t* data, uint8_t* crc) { // Function to parse the received data
        *id = buffer[0]; // Slave address
        *func = buffer[1]; // Function code
        *byte_num = buffer[2]; // Number of bytes
        data[3] = buffer[3]; // High byte of temperature
        data[4] = buffer[4]; // Low byte of temperature
        data[5] = buffer[5]; // High byte of humidity
        data[6] = buffer[6]; // Low byte of humidity
        *crc = (buffer[7] << 8) | buffer[8]; // CRC value
    }
    void processReceivedData(uint8_t* buffer) { // Function to process the received data
        uint8_t id, func, byte_num, crc;
        uint8_t sensor_data[4]; // Array to hold the temperature and humidity data
        parseData(buffer, &id, &func, &byte_num, sensor_data, &crc); // Parse the received data
        if(id == slave_address && func == 0x03 && byte_num == 4) { // Check if the response is valid
        // Combine high and low bytes to get temperature and humidity
            data.temperature_value = ((sensor_data[3] << 8) | sensor_data[4]) / 10.0; // Convert to Celsius
            data.humidity_value = ((sensor_data[5] << 8) | sensor_data[6]) / 10.0; // Convert to percentage
        }
    }
    void readSensor() { // Function to read the sensor data
        prepareBuffer(); // Prepare the Modbus request buffer
        // Prepare the Modbus request
        ModbusRequest_t request; // Create a Modbus request structure
        prepareModbusRequest(&request, tx_buffer, 8, 200, rx_buffer, 9, xTaskGetCurrentTaskHandle()); // Prepare the Modbus request
        // Send the Modbus request to the queue
        sendModbusQueue(request, 0); // Send the request with normal priority
    }
    float getTemperature() { // Function to get the temperature data
        return data.temperature_value; // Return the temperature value
    }
    float getHumidity() { // Function to get the humidity data
        return data.humidity_value; // Return the humidity value
    }
};