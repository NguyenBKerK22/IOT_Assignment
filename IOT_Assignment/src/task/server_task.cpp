#include "server_task.h"

TaskHandle_t serverTask_handle = NULL;

ThingsBoard *tb = nullptr;
Arduino_MQTT_Client *mqttClient = nullptr;

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
        TinyGsmClient *client4G = new TinyGsmClient(get_sim_client());
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

    tb = new ThingsBoard(*mqttClient, MAX_MESSAGE_RECEIVE_SIZE, MAX_MESSAGE_SEND_SIZE, Default_Max_Stack_Size);

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
            Serial.println("THINGSBOARD_SERVER: " + String(THINGSBOARD_SERVER));
            Serial.println("THINGSBOARD_PORT: " + String(THINGSBOARD_PORT));
            Serial.println("TOKEN: " + device_config_data.token);
            const char token[] = "NodeMCU-T1";
            if (tb->connect(THINGSBOARD_SERVER, token, THINGSBOARD_PORT))
            {
                Serial.println("Connected to Server");
            }
            else
            {
                Serial.println("Connected to server fail");
                vTaskDelay(pdMS_TO_TICKS(5000));
                continue;
            }
        }

        if (tb)
            tb->loop();

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void initServerTask(void)
{
    xTaskCreate(serverTask, "configTask", 1024 * 5, NULL, 2, &serverTask_handle);
    vTaskSuspend(serverTask_handle);
}
