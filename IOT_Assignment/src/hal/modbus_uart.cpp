#include "modbus_uart.h"

HardwareSerial modbusSerial(1);
uint8_t modbus_hardware_status = 0;

void modbus_uart_init(void){
    // Initialize the UART with the specified parameters
    pinMode(MAX_485_DE_RE_PIN, OUTPUT);
    modbusSerial.begin(MODBUS_UART_BAUDRATE, SERIAL_8N1, MODBUS_UART_RX_PIN, MODBUS_UART_TX_PIN);
    modbusSerial.setTimeout(MODBUS_UART_TIMEOUT);
    modbus_hardware_status = 1;
    digitalWrite(MAX_485_DE_RE_PIN, LOW); // Set DE/RE pin low to disable transmission
    while (modbusSerial.available()) {
        modbusSerial.read();
    }
};
void modbus_uart_send(uint8_t *data, uint16_t length){
    // Send data over UART
    digitalWrite(MAX_485_DE_RE_PIN, HIGH); // Set DE/RE pin high to enable transmission
    modbusSerial.write(data, length);
    modbusSerial.flush(); // Ensure all data is sent
    digitalWrite(MAX_485_DE_RE_PIN, LOW); // Set DE/RE pin low to disable transmission
};
size_t modbus_uart_receive(uint8_t *data, uint16_t length){
    // Read data from UART
    size_t bytesRead = 0;
    uint32_t startTime = millis();

    // Polling loop: chờ cho đến khi có đủ dữ liệu hoặc hết thời gian timeout
    while ((millis() - startTime) < 1000) {
        if (modbusSerial.available() >= length) {
            bytesRead = modbusSerial.readBytes(data, length);
            break;
        }
        delay(1); // Nhường CPU cho task khác
    }

    return bytesRead; // Trả về số byte thực sự đã đọc (có thể < length nếu timeout)
}

uint8_t modbus_is_started(){
    return modbus_hardware_status == 1;
}

