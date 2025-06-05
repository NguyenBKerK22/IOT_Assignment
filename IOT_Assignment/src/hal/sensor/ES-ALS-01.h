#include <Arduino.h>
#include "hal/modbus_uart.h"
#include "CRC16.h"
#include "hal/modbus_queue.h"
#include "hal/crc.h"
struct es_als_01_data {
  int light_intensity; // Light intensity in lux
};
struct es_als_01 {
    uint8_t slave_address; // Slave address for the sensor
    uint8_t tx_buffer[8]; 
    uint8_t rx_buffer[256]; // Buffer to hold the data
    es_als_01_data data; // Data structure to hold pH value
    es_als_01(uint8_t address) : slave_address(address) { // Constructor to initialize the slave address
        memset(tx_buffer, 0, sizeof(tx_buffer)); // Initialize tx_buffer to zero
        memset(rx_buffer, 0, sizeof(rx_buffer)); // Initialize rx_buffer to zero
    }
    void prepareBuffer() { // Function to prepare the Modbus request buffer
        // Buffer to hold the data     
        tx_buffer[0] = slave_address; // Slave address
        tx_buffer[1] = 0x03; // Function code for reading holding registers
        tx_buffer[2] = 0x00; // Starting address high byte
        tx_buffer[3] = 0x02; // Starting address low byte
        tx_buffer[4] = 0x00; // Number of registers high byte
        tx_buffer[5] = 0x02; // Number of registers low byte
        // Calculate CRC (Cyclic Redundancy Check) for error checking
        uint16_t crc_result = crc16(tx_buffer, 6); // Calculate CRC for the first 6 bytes
        tx_buffer[7] = crc_result >> 8; // CRC high byte
        tx_buffer[6] = crc_result & 0xFF; // CRC low byte
    }
    void parseData(uint8_t* buffer, uint8_t* id, uint8_t* func, uint8_t* byte_num, uint32_t* data, uint8_t* crc) { // Function to process the received data
        *id = buffer[0]; // Slave address
        *func = buffer[1]; // Function code
        *byte_num = buffer[2]; // Number of bytes
        *data = 0; // Initialize data to zero

        for(int i = 0; i < 4; i++) { // Read 4 bytes of data
            (*data) = (*data) << 8 | buffer[i + 3]; // Store the data bytes
        }
        *crc = (buffer[7] << 8) | buffer[8]; // CRC value     
    }
    void processReceivedData(uint8_t* buffer) { // Function to process the received data
        uint8_t id, func, byte_num, crc;
        uint32_t sensor_data = 0; // Array to hold the pH value
        parseData(buffer, &id, &func, &byte_num, &sensor_data, &crc); // Parse the received data
        if(id == slave_address && func == 0x03 && byte_num == 4) { // Check if the response is valid
            data.light_intensity = sensor_data; // Store the light intensity value
        } 
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer after processing
    }
    void readSensor() { // Function to read the sensor data
        prepareBuffer(); // Prepare the Modbus request buffer
        // Prepare the Modbus request
        ModbusRequest_t request; // Create a Modbus request structure
        prepareModbusRequest(&request, tx_buffer, 8, 200, rx_buffer, 9, xTaskGetCurrentTaskHandle()); // Prepare the Modbus request
        // Send the Modbus request to the queue
        sendModbusQueue(request, 0); // Send the request with normal priority

    }
    int getlight() { // Function to get the pH value
        return data.light_intensity; // Return the pH value
    }
};