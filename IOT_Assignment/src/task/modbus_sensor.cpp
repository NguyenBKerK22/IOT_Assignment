#include "modbus_sensor.h"

es_als_01 light_sensor(0x04);         // Create an instance of the ES-ALS-01 sensor with slave address 0x01
es_ws_02 wind_sensor(0x02);           // Create an instance of the ES-WS-02 sensor with slave address 0x02
sd123_st01v3 temp_humid_sensor(0x01); // Create an instance of the ES-SM-THEC-01 sensor with slave address 0x03

TaskHandle_t xLightSensorTaskHandle = NULL;
TaskHandle_t xWindSensorTaskHandle = NULL;
TaskHandle_t xTempHumidSensorTaskHandle = NULL;
TaskHandle_t xModbusHandlerTaskHandle = NULL;

void light_sensor_task(void *pvParameters)
{
    while (1)
    {
        light_sensor.readSensor();
        // vTaskSuspend(NULL); // Suspend the task until the data is received
        if (!ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(2000)) == 0)
        {
            light_sensor.processReceivedData(light_sensor.rx_buffer); // Process the received data
            int lux = light_sensor.getlight();
            Serial.print("Light: ");
            Serial.println(lux);

            tb->sendTelemetryData(KEY_LIGHT_AMBIENT, lux);
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
void wind_sensor_task(void *pvParameters)
{
    while (1)
    {
        wind_sensor.readSensor();
        // vTaskSuspend(NULL); // Suspend the task until the data is received
        if (!ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(2000)) == 0){
        // Process the received data
            wind_sensor.processReceivedData(wind_sensor.rx_buffer); // Process the received data
            int wind = wind_sensor.getWindSpeed();
            Serial.print("Wind: ");
            Serial.println(wind);

            tb->sendTelemetryData(KEY_WINDSPEAD, wind);
        }
        vTaskDelay(pdMS_TO_TICKS(6000));
    }
}
void temp_humid_sensor_task(void *pvParameters)
{
    while (1)
    {
        temp_humid_sensor.readSensor();
        // vTaskSuspend(NULL); // Suspend the task until the data is received
        if(!ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(2000)) == 0)
        {
            temp_humid_sensor.processReceivedData(temp_humid_sensor.rx_buffer); // Process the received data
            float temperature = temp_humid_sensor.getTemperature();             // Get the temperature value
            float humidity = temp_humid_sensor.getHumidity();                   // Get the humidity value
            Serial.print("Temperature: ");
            Serial.print(temperature);
            Serial.print(" °C, Humidity: ");
            Serial.print(humidity);
            Serial.println(" %");

            tb->sendTelemetryData(KEY_HUMIDITY, humidity);
            tb->sendTelemetryData(KEY_TEMPERATURE, temperature);
        }

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
void modbus_handler_task(void *pvParameters)
{
    ModbusRequest_t request;
    while (1)
    {
        if (xQueueReceive(xModbusQueue, &request, portMAX_DELAY) == pdTRUE)
        {
            // Process the Modbus request
            modbus_uart_send(request.data, 8);                         // Send the Modbus request over UART
            modbus_uart_receive(request.slave_buffer, request.length); // Receive the response from the Modbus slave
            // Here you can add your Modbus processing logic
            // For example, send the request to the Modbus slave and wait for a response
            // After processing, you can notify the task that sent the request
           xTaskNotifyGive(request.task_handle);        
        }
    }
}

void initModbusTasks()
{
    // put your setup code here, to run once:
    // Initialize serial communication at 115200 baud rate
    initModbusQueue();                                                                        // Initialize the Modbus queue
    modbus_uart_init();                                                                       // Initialize the Modbus UART communication
    xTaskCreate(wind_sensor_task, "Wind Sensor Task", 5120, NULL, 1, &xWindSensorTaskHandle); // Create a task for reading wind sensor data
    vTaskSuspend(xWindSensorTaskHandle);                                                      // Suspend the wind sensor task until data is received

    xTaskCreate(light_sensor_task, "Light Sensor Task", 5120, NULL, 1, &xLightSensorTaskHandle); // Create a task for reading wind sensor data
    vTaskSuspend(xLightSensorTaskHandle);                                                        // Suspend the light sensor task until data is received

    xTaskCreate(temp_humid_sensor_task, "Temperature Handler Task", 5120, NULL, 1, &xTempHumidSensorTaskHandle); // Create a task for handling Modbus requests
    vTaskSuspend(xTempHumidSensorTaskHandle);                                                                    // Suspend the temperature and humidity sensor task until data is received

    xTaskCreate(modbus_handler_task, "Modbus Handler Task", 5120, NULL, 4, &xModbusHandlerTaskHandle); // Create a task for handling Modbus requests
    vTaskSuspend(xModbusHandlerTaskHandle);                                                            // Suspend the temperature and humidity sensor task until data is received
}