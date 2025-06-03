#include <Arduino.h>
#include "hal/modbus_uart.h"
#include "CRC16.h"
#include "hal/modbus_queue.h"
#include "utils.h"
#include "crc/crc.h"
struct es_ws_02_data {
    uint16_t windSpeed; // Wind speed in m/s
};
struct es_ws_02 {
    uint8_t slave_address; // Slave address for the sensor
    uint8_t tx_buffer[8];
    uint8_t rx_buffer[256]; // Buffer to hold the data
    es_ws_02_data data; // Data structure to hold wind speed data
    es_ws_02(uint8_t address) : slave_address(address) { // Constructor to initialize the slave address
        memset(tx_buffer, 0, sizeof(tx_buffer)); // Initialize tx_buffer to zero
        memset(rx_buffer, 0, sizeof(rx_buffer)); // Initialize rx_buffer to zero
    }
    void prepareBuffer() { // Function to prepare the Modbus request buffer
        // Buffer to hold the data
        tx_buffer[0] = slave_address; // Slave address
        tx_buffer[1] = 0x03; // Function code for reading holding registers
        tx_buffer[2] = 0x00; // Starting address high byte
        tx_buffer[3] = 0x00; // Starting address low byte
        tx_buffer[4] = 0x00; // Number of registers high byte
        tx_buffer[5] = 0x01; // Number of registers low byte
        // Calculate CRC (Cyclic Redundancy Check) for error checking
        uint16_t crc_result = crc16(tx_buffer, 6); // Calculate CRC for the first 6 bytes
        tx_buffer[7] = crc_result >> 8; // CRC high byte
        tx_buffer[6] = crc_result & 0xFF; // CRC low byte
    }
    void parseData(uint8_t* buffer, uint8_t* id, uint8_t* func, uint8_t* byte_num, uint16_t* data, uint8_t* crc) { // Function to parse the received data
        *id = buffer[0]; // Slave address
        *func = buffer[1]; // Function code
        *byte_num = buffer[2]; // Number of bytes
        *data = (buffer[3] << 8) | buffer[4]; // Combine high and low bytes to get wind speed
        *crc = (buffer[5] << 8) | buffer[6]; // CRC value
    }
    void processReceivedData(uint8_t* buffer) { // Function to process the received data
        uint8_t id, func, byte_num, crc;
        uint16_t sensor_data; // Array to hold the wind speed data
        parseData(buffer, &id, &func, &byte_num, &sensor_data, &crc); // Parse the received data
        if(id == slave_address && func == 0x03 && byte_num == 2) { // Check if the response is valid
            data.windSpeed = sensor_data; // Store the wind speed value
        } 
    }
    void readSensor() { // Function to read the sensor data 
        prepareBuffer(); // Prepare the Modbus request buffer
        // Prepare the Modbus request
        ModbusRequest_t request; // Create a Modbus request structur
        prepareModbusRequest(&request, tx_buffer, 8, 200, rx_buffer, 7, xTaskGetCurrentTaskHandle()); // Prepare the Modbus request
        // Send the Modbus request to the queue
        sendModbusQueue(request, 0); // Send the request with normal priority
        // modbus_uart_send(tx_buffer, 8); // Send the Modbus request over UAR
        // modbus_uart_receive(rx_buffer, 7); // Receive the response from the Modbus slave
        // vTaskDelay(pdMS_TO_TICKS(200)); // Wait for the specified time to read the response
    }
    int getWindSpeed() { // Function to get the wind speed data
        return data.windSpeed; // Return the wind speed value
    }
};