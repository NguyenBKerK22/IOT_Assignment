#include "modbus_uart.h"

HardwareSerial modbusSerial(2);

uint8_t modbus_hardware_status = 0;

void modbus_uart_init(void){
    // Initialize the UART with the specified parameters
    modbusSerial.begin(MODBUS_UART_BAUDRATE, SERIAL_8N1, MODBUS_UART_RX_PIN, MODBUS_UART_TX_PIN);
    modbusSerial.setTimeout(MODBUS_UART_TIMEOUT);
    modbus_hardware_status = 1;
};
void modbus_uart_send(uint8_t *data, uint16_t length){
    // Send data over UART
    modbusSerial.write(data, length);
    modbusSerial.flush(); // Ensure all data is sent
};
size_t modbus_uart_receive(uint8_t *data, uint16_t length){
    // Read data from UART
    size_t bytesRead = modbusSerial.readBytes(data, length);
    return bytesRead;
};

uint8_t modbus_is_started(){
    return modbus_hardware_status == 1;
}

