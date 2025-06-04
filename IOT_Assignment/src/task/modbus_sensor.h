#include <Arduino.h>
#include "sensor/SD123-ST01V3.h"
#include "sensor/ES-WS-02.h"
#include "sensor/ES-ALS-01.h"
#include "hal/modbus_queue.h"
extern es_als_01 light_sensor; // Create an instance of the ES-ALS-01 sensor with slave address 0x01
extern es_ws_02 wind_sensor; // Create an instance of the ES-WS-02 sensor with slave address 0x02
extern sd123_st01v3 temp_humid_sensor; // Create an instance of the ES-SM-THEC-01 sensor with slave address 0x03

extern TaskHandle_t xLightSensorTaskHandle;
extern TaskHandle_t xWindSensorTaskHandle;
extern TaskHandle_t xTempHumidSensorTaskHandle;
extern TaskHandle_t xModbusHandlerTaskHandle;
void light_sensor_task(void* pvParameters);
void wind_sensor_task(void* pvParameters) ;
void temp_humid_sensor_task(void* pvParameters) ;
void modbus_handler_task(void* pvParameters);
void initModbusTasks();