#include "global.h"
struct es_sm_thec_01_data {
  float temperature_value; // Temperature in Celsius
  float humidity_value; // Humidity in percentage
  float electrical_value; // Pressure in hPa
};
struct es_sm_thec_01 {
    uint8_t slave_address; // Slave address for the sensor
    uint8_t tx_buffer[8]; // Buffer to hold the data
    uint8_t rx_buffer[11]; // Buffer to hold the received data
    es_sm_thec_01_data data; // Data structure to hold temperature, humidity, and pressure data
    CRC16 crc; // CRC object for error checking
    es_sm_thec_01_data readSensor() { // Function to read the sensor data
        tx_buffer[0] = slave_address; // Slave address
        tx_buffer[1] = 0x03; // Function code for reading holding registers
        tx_buffer[2] = 0x00; // Starting address high byte
        tx_buffer[3] = 0x00; // Starting address low byte
        tx_buffer[4] = 0x00; // Number of registers high byte
        tx_buffer[5] = 0x03; // Number of registers low byte
        // Calculate CRC (Cyclic Redundancy Check) for error checking
        crc.add((uint8_t *) tx_buffer, 6); // Initial CRC value
        uint16_t crc_result = crc.getCRC(); // Get the CRC value
        tx_buffer[6] = crc_result >> 8; // CRC high byte
        tx_buffer[7] = crc_result & 0xFF; // CRC low byte
        // Send the tx_buffer to the sensor
        modbus_uart_send(tx_buffer, 8); // Send the data over UART
        // Receive the response from the sensor
        size_t bytesRead = modbus_uart_receive(rx_buffer, 11); // Read the response
        if (bytesRead == 11) { // Check if the response is valid
            data.temperature_value = (rx_buffer[3] << 8) | rx_buffer[4]; // Combine high and low bytes to get the pH value
            data.humidity_value = (rx_buffer[5] << 8) | rx_buffer[6]; // Combine high and low bytes to get the humidity value
            data.electrical_value = (rx_buffer[7] << 8) | rx_buffer[8]; // Combine high and low bytes to get the pressure value
            uint16_t crc_received = (rx_buffer[9] << 8) | rx_buffer[10]; // Get the received CRC value
            crc.add((uint8_t *) rx_buffer, 9); // Calculate CRC for the received data
            uint16_t crc_calculated = crc.getCRC(); // Get the calculated CRC value
            if (crc_received != crc_calculated) { // Check if the CRC matches
                Serial.println("CRC error!"); // Print error message if CRC does not match
            }
        } else {
            Serial.println("Error reading sensor data!"); // Print error message if reading fails
        }
        memset(tx_buffer, 0, sizeof(tx_buffer)); // Clear the tx_buffer
        memset(rx_buffer, 0, sizeof(rx_buffer)); // Clear the rx_buffer
        return data;
    }
    void setSlaveAddress(uint8_t address) { // Function to set the slave address
        slave_address = address; // Set the slave address
        tx_buffer[0] = slave_address; // Slave address
        tx_buffer[1] = 0x10; // Function code for reading holding registers
        tx_buffer[2] = 0x07; // Starting address high byte
        tx_buffer[3] = 0xD0; // Starting address low byte
        tx_buffer[4] = 0x00; // Number of registers high byte
        tx_buffer[5] = 0x01; // Number of registers low byte
        // Calculate CRC (Cyclic Redundancy Check) for error checking
        crc.add((uint8_t *) tx_buffer, 6); // Initial CRC value
        uint16_t crc_result = crc.getCRC(); // Get the CRC value
        tx_buffer[6] = crc_result >> 8; // CRC high byte
        tx_buffer[7] = crc_result & 0xFF; // CRC low byte
        modbus_uart_send(tx_buffer, 8); // Send the data over UART
        // Receive the response from the sensor
        size_t bytesRead = modbus_uart_receive(rx_buffer, 7); // Read the response
        if (bytesRead == 7) { // Check if the response is valid
            uint16_t crc_received = (rx_buffer[5] << 8) | rx_buffer[6]; // Get the received CRC value
            crc.add((uint8_t *) rx_buffer, 5); // Calculate CRC for the received data
            uint16_t crc_calculated = crc.getCRC(); // Get the calculated CRC value
            if (crc_received != crc_calculated) { // Check if the CRC matches
                Serial.println("CRC error!"); // Print error message if CRC does not match
            }
        } else {
            Serial.println("Error reading sensor data!"); // Print error message if reading fails
        }
        memset(tx_buffer, 0, sizeof(tx_buffer)); // Clear the tx_buffer
        memset(rx_buffer, 0, sizeof(rx_buffer)); // Clear the rx_buffe
    }
};