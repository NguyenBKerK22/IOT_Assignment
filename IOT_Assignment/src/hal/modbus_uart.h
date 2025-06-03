#ifndef MODBUS_UART_H
#define MODBUS_UART_H
// INCLUDE
#include <Arduino.h>
#include <HardwareSerial.h>

// DEFINES
#define MODBUS_UART_TX_PIN GPIO_NUM_17 // TX pin for Modbus UART
#define MODBUS_UART_RX_PIN GPIO_NUM_16 // RX pin for Modbus UART

#define MODBUS_UART_BAUDRATE 9600 // default relay baudrate is 115200
#define MODBUS_UART_TIMEOUT 1000 // Timeout in milliseconds

#define MAX_485_DE_RE_PIN GPIO_NUM_5 // RE pin for RS485 communication
/**
 * @brief Initialize the UART for Modbus communication
 *
 * @return
 *     - None
 */
void modbus_uart_init(void);

/**
 * @brief Send modbus data over UART
 *
 * @param data      Pointer to the data to be sent.
 * @param length    Data length
 *
 * @return
 *     - None
 */
void modbus_uart_send(uint8_t *data, uint16_t length);

/**
 * @brief Receive modbus data over UART
 *
 * @param data      Pointer to the buffer to store received data.
 * @param length    Maximum length of data to receive.
 *
 * @return
 *     - (-1) Error
 *     - OTHERS (>=0) The number of bytes received
 */
size_t modbus_uart_receive(uint8_t *data, uint16_t length);


/**
 * @brief Check if Modbus UART is started
 *
 * @return
 *     - 1 if started
 *     - 0 if not started
 */
uint8_t modbus_is_started(void);
#endif