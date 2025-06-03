#ifndef MODBUS_QUEUE_H
#define MODBUS_QUEUE_H
#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#define MODBUS_QUEUE_LENGTH 10

extern xQueueHandle xModbusQueue;
typedef struct {
    uint8_t* data;
    uint16_t time_read;
    uint8_t timeout;
    uint8_t* slave_buffer;    
    uint8_t length; // Length of the data to be read
    TaskHandle_t task_handle;
    
} ModbusRequest_t;

void initModbusQueue(void);
void sendModbusQueue(ModbusRequest_t request, uint8_t priority);
void prepareModbusRequest(ModbusRequest_t* request, uint8_t* data, uint16_t time_read, uint8_t timeout, uint8_t* slave_buffer, uint8_t length, TaskHandle_t task_handle);



#endif // MODBUS_QUEUE_H