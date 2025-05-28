#include "modbus_queue.h"

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
