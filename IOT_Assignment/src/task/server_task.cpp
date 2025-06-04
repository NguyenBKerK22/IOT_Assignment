#include "server_task.h"

TaskHandle_t serverTask_handle = NULL;

// Statuses for subscribing to rpc
bool subscribed = false;

void serverTask(void *pvParameters)
{

    if (tb != nullptr)
    {
        delete tb;
        tb = nullptr;
    }

    if (mqttClient != nullptr)
    {
        delete mqttClient;
        mqttClient = nullptr;
    }

    if (device_config_data.is4G && device_config_data.isWifi)
    {
        Serial.println("Multiple connection error");
    }

    if (device_config_data.is4G)
    {
        TinyGsmClient* client4G = get_sim_client();
        mqttClient = new Arduino_MQTT_Client(*client4G);
    }
    else if (device_config_data.isWifi)
    {
        WiFiClient *wifiClient = new WiFiClient();
        mqttClient = new Arduino_MQTT_Client(*wifiClient);
    }

    mqttClient->set_server(THINGSBOARD_SERVER, THINGSBOARD_PORT);

    if (!mqttClient->connected())
    {
        Serial.println("MQTT client not connected.");
    }
    else
    {
        Serial.println("MQTT client is connected.");
    }

    tb = new ThingsBoard(*mqttClient, MAX_MESSAGE_RECEIVE_SIZE, MAX_MESSAGE_SEND_SIZE, Default_Max_Stack_Size, apis);

    bool first_time = true;
    while (true)
    {
        if (device_config_data.isWifi && WiFi.status() != WL_CONNECTED)
        {
            Serial.println("WiFi not connected");
            vTaskDelay(pdMS_TO_TICKS(5000));
            continue;
        }

        if (tb && !tb->connected())
        {
            if (tb->connect(THINGSBOARD_SERVER, device_config_data.token.c_str(), THINGSBOARD_PORT))
            {
                if (first_time)
                {
                    first_time = false;
                    vTaskResume(xLightSensorTaskHandle);
                    vTaskResume(xWindSensorTaskHandle);
                    vTaskResume(xTempHumidSensorTaskHandle);
                    vTaskResume(xModbusHandlerTaskHandle);
                }
                Serial.println("Connected to Server");
            }
            else
            {
                Serial.println("Connected to server fail");
                vTaskDelay(pdMS_TO_TICKS(5000));
                continue;
            }
        }

        if (!subscribed)
        {
            Serial.println("Subscribing for RPC...");
            const std::array<RPC_Callback, MAX_RPC_SUBSCRIPTIONS> callbacks = {
                // Internal size can be 0, because if we use the JsonDocument as a JsonVariant and then set the value we do not require additional memory
                RPC_Callback{SCHEDULER_TURNON_MORNING_METHOD, processSchedulerMorning},
                RPC_Callback{SCHEDULER_TURNON_AFTERNOON_METHOD, processSchedulerAfternoon},
                RPC_Callback{RPC_SET_RELAY_METHOD, processSetRelayState},
                RPC_Callback{RPC_GET_RELAY_METHOD, processGetRelayState}};

            if (!rpc.RPC_Subscribe(callbacks.cbegin(), callbacks.cend()))
            {
                Serial.println("Failed to subscribe for RPC");
                return;
            }

            Serial.println("Subscribe done");
            subscribed = true;
        }

        if (tb)
            tb->loop();

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void initServerTask(void)
{
    xTaskCreate(serverTask, "configTask", 1024 * 5, NULL, 1, &serverTask_handle);
    vTaskSuspend(serverTask_handle);
}
