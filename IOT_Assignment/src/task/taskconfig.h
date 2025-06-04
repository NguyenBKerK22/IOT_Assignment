#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "global.h"

#define MAX_TASK 10

extern TaskHandle_t serverTask_handle;
extern TaskHandle_t modbushandleTask_handle;
extern TaskHandle_t handlerResetTask_handle;
extern TaskHandle_t configTask_handle;
extern TaskHandle_t handlerResetTask_handle;

extern TaskHandle_t xLightSensorTaskHandle;
extern TaskHandle_t xWindSensorTaskHandle;
extern TaskHandle_t xTempHumidSensorTaskHandle;
extern TaskHandle_t xModbusHandlerTaskHandle;
