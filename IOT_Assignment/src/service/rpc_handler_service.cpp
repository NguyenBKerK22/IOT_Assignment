#include "rpc_handler_service.h"

/*
    Define RPC callback handler for controlling the RS485 relay
    RS485 Relay used for turning on/off:
    + Pump
    + Awning
    + Fogger
*/

void processGetRelayState(const JsonVariantConst &data, JsonDocument &response)
{
    Serial.println("Received the get Initiate State");
    response["1"] = digitalRead(PUMP) ? "true" : "false";
    response["2"] = digitalRead(FOGGER) ? "true" : "false";
    response["3"] = digitalRead(AWNING) ? "true" : "false";
}

void processSetRelayState(const JsonVariantConst &data, JsonDocument &response)
{
    Serial.println("Received the set switch method");

    // Parse pin & state
    uint8_t pinIndex = data["pin"] | 0;     // Lấy giá trị "pin", mặc định 0 nếu không có
    bool enabled = data["enabled"] | false; // Lấy giá trị "enabled", mặc định false

    // Debug thông tin đầu vào
    Serial.printf("Pin index: %d, Enabled: %s\n", pinIndex, enabled ? "true" : "false");

    // Ánh xạ từ chỉ số pin sang chân GPIO tương ứng
    int targetPin = -1;
    switch (pinIndex)
    {
    case 1:
        targetPin = PUMP;
        break;
    case 2:
        targetPin = FOGGER;
        break;
    case 3:
        targetPin = AWNING;
        break;
    default:
        Serial.println("Invalid pin index!");
        response["error"] = "Invalid pin index";
        return;
    }

    // Điều khiển trạng thái relay
    digitalWrite(targetPin, enabled ? HIGH : LOW);

    // Phản hồi trạng thái tất cả relay
    switch (targetPin)
    {
    case PUMP:
        /* code */
        response["1"] = digitalRead(PUMP) ? "true" : "false";
        break;
    case FOGGER:
        /* code */
        response["2"] = digitalRead(FOGGER) ? "true" : "false";
        break;
    case AWNING:
        /* code */
        response["3"] = digitalRead(AWNING) ? "true" : "false";
        break;

    default:
        break;
    }
}

/*
    Define RPC callback handler for processing the scheduler controll

*/

void processSchedulerMorning(const JsonVariantConst &data, JsonDocument &response)
{
    Serial.println("Received turnOnSchedulerMorning RPC");
    xTaskCreate(
        pumpTask,   // task function
        "PumpTask", // name
        2048,       // stack size
        NULL,       // param
        1,          // priority
        NULL        // task handle
    );
}

void processSchedulerAfternoon(const JsonVariantConst &data, JsonDocument &response)
{
    Serial.println("Received turnOnSchedulerAfternoon RPC");
    xTaskCreate(
        pumpTask,   // task function
        "PumpTask", // name
        2048,       // stack size
        NULL,       // param
        1,          // priority
        NULL        // task handle
    );
}

/*

*/

void pumpTask(void *pvParameters)
{
    Serial.println("Pumping...");
    digitalWrite(PUMP, HIGH);
    vTaskDelay(pdMS_TO_TICKS(5000)); // chờ 5 giây
    digitalWrite(PUMP, LOW);
    Serial.println("Done Pump");
    vTaskDelete(NULL); // xóa task sau khi xong
}