#ifndef MODBUS_HADNLER_TASK_H
#define MODBUS_HANDLER_TASK_H
#pragma once 

#include "hal/modbus_queue.h"
#include "taskconfig.h"



void initModbusHandlerTask(void);
void modbushandlerTask(void* pvParameters);




#endif // MODBUS_HANDLER_TASK_H