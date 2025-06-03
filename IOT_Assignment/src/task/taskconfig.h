#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define MAX_TASK 10

extern TaskHandle_t serverTask_handle;
extern TaskHandle_t modbushandleTask_handle;
extern TaskHandle_t handlerResetTask_handle;
