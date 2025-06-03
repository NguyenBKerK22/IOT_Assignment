#include "modbus_queue.h"
xQueueHandle xModbusQueue;
void initModbusQueue(void)
{
    xModbusQueue = xQueueCreate(MODBUS_QUEUE_LENGTH, sizeof(ModbusRequest_t));
}

void sendModbusQueue(ModbusRequest_t request, uint8_t priority)
{
    if(priority == 1){
        xQueueSendToFront(xModbusQueue, &request, portMAX_DELAY);
    }
    else{
        xQueueSend(xModbusQueue, &request, portMAX_DELAY);
    }
}
void prepareModbusRequest(ModbusRequest_t* request, uint8_t* data, uint16_t time_read, uint8_t timeout, uint8_t* slave_buffer, uint8_t length ,TaskHandle_t task_handle)
{
    request->data = data;
    request->time_read = time_read;
    request->timeout = timeout;
    request->slave_buffer = slave_buffer;
    request->length = length;
    request->task_handle = task_handle;
}