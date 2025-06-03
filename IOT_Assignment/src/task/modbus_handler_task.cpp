#include "modbus_handler_task.h"


TaskHandle_t modbushandleTask_handle = NULL;


void initModbusHandlerTask(void)
{
    xTaskCreate(modbushandlerTask, "modbushandlerTask", 1024 * 5, NULL, 5, &modbushandleTask_handle);
}


void modbushandlerTask(void* pvParameters)
{

    
    while(true){

    }

}
