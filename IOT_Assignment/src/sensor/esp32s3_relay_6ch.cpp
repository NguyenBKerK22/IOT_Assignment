#include "esp32s3_relay_6ch.h"

uint8_t relay_status[3] = {0, 0, 0}; // Array to hold the status of each relay channel
void RELAY_init(void){
    if(modbus_is_started() == 0){
        modbus_uart_init(); // Initialize Modbus UART if not started
    };
    uint8_t command[] = {0x06, 0x05, 0x00, 0xFF, 0x00, 0x00, 0xFC, 0x4D}; // Turn off all relays
    modbus_uart_send(command, sizeof(command));
    relay_status[0] = 0; // Set channel 1 status to OFF
    relay_status[1] = 0; // Set channel 2 status to OFF 
    relay_status[2] = 0; // Set channel 3 status to OFF
};
void RELAY_toggle_ch1(void){
    if(modbus_is_started() == 0){
        modbus_uart_init(); // Initialize Modbus UART if not started
    };
    uint8_t command[] = {0x06, 0x05, 0x00, 0x01, 0x55, 0x00, 0xA2, 0xED}; // Example command to toggle relay channel 1
    modbus_uart_send(command, sizeof(command));
    relay_status[0] = !relay_status[0];
};
void RELAY_toggle_ch2(void){
    if(modbus_is_started() == 0){
        modbus_uart_init(); // Initialize Modbus UART if not started
    };
    uint8_t command[] = {0x06, 0x05, 0x00, 0x02, 0x55, 0x00, 0x52, 0xED}; // Example command to toggle relay channel 2
    modbus_uart_send(command, sizeof(command));
    relay_status[1] = !relay_status[1];
};
void RELAY_toggle_ch3(void){
    if(modbus_is_started() == 0){
        modbus_uart_init(); // Initialize Modbus UART if not started
    };
    uint8_t command[] = {0x06, 0x05, 0x00, 0x03, 0x55, 0x00, 0x03, 0x2D}; // Example command to toggle relay channel 3
    modbus_uart_send(command, sizeof(command));
    relay_status[2] = !relay_status[2];
};

uint8_t RELAY_get_status_ch1(){
    return relay_status[0]; // Return the status of channel 1
};
uint8_t RELAY_get_status_ch2(){
    return relay_status[1]; // Return the status of channel 1
};
uint8_t RELAY_get_status_ch3(){
    return relay_status[2]; // Return the status of channel 1
};
