#ifndef ESP32S3_RELAY_6CH_H
#define ESP32S3_RELAY_6CH_H

#include <Arduino.h>
#include "hal/modbus_uart.h"

/**
 * @brief Initialize the relay module, turning off all channels.
 *
 * @return
 *     - None
 */
void RELAY_init(void);

/**
 * @brief Toggle the status of relay channel 1
 *
 * @return
 *     - None
 */
void RELAY_toggle_ch1(void);

/**
 * @brief Toggle the status of relay channel 2
 *
 * @return
 *     - None
 */
void RELAY_toggle_ch2(void);

/**
 * @brief Toggle the status of relay channel 3
 *
 * @return
 *     - None
 */
void RELAY_toggle_ch3(void);

/**
 * @brief Get current status of relay channel 1
 *
 * @return
 *     - Relay status: 1 for ON, 0 for OFF
 */
uint8_t RELAY_get_status_ch1();

/**
 * @brief Get current status of relay channel 2
 *
 * @return
 *     - Relay status: 1 for ON, 0 for OFF
 */
uint8_t RELAY_get_status_ch2();

/**
 * @brief Get current status of relay channel 3
 *
 * @return
 *     - Relay status: 1 for ON, 0 for OFF
 */
uint8_t RELAY_get_status_ch3();

#endif // ESP32S3_RELAY_6CH_H