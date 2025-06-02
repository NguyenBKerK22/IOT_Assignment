#ifndef SIM_MODULE_H
#define SIM_MODULE_H

#define TINY_GSM_MODEM_SIM7600
#include <HardwareSerial.h>
#include <TinyGsmClient.h>

// ============================== README BEFORE USE ==============================
// This module is designed to work with the SIM7600 modem.
// TinyGsmClient need to be wrapped with Arduino MQTT client to construct ThingsBoard object.
// Make sure to change the thingsboard client to TinyGsmClient in your code (when switching between wifi-4g).
// ===============================================================================

// Define default APN, USERNAME, and PASSWORD for different mobile networks
#define APN_VINAPHONE       "m3_world"
#define USERNAME_VINAPHONE  "mms"
#define PASSWORD_VINAPHONE  "mms"

#define APN_VIETTEL         "v-internet"
#define USERNAME_VIETTEL    ""
#define PASSWORD_VIETTEL    ""

#define APN_MOBIFONE        "m-wap"
#define USERNAME_MOBIPHONE  "mms"
#define PASSWORD_MOBIPHONE  "mms"

/**
 * @brief Get the TinyGsmClient instance for the SIM module. 
 *
 * @return
 *     - TinyGsmClient instance
 */
TinyGsmClient get_sim_client();

/**
 * @brief Set the APN, username, and password for the SIM module.
 *
 * @param apn      Access Point Name 
 * @param username Username for the APN (optional)
 * @param password Password for the APN (optional)
 *
 * @return
 *     - None
 */
void set_apn(const String &apn, const String &username = "", const String &password = "");

/**
 * @brief Initialize the SIM module.
 *
 * @return
 *     - None
 */
void init_sim();

/**
 * @brief Connect to the network and establish a GPRS connection.
 *
 * @return
 *     - None
 */
void run_sim();

#endif