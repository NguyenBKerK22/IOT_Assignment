#ifndef SERVER_TASK_H
#define SERVER_TASK_H
#pragma once

#include "hal/module_sim.h"
#include "service/connection_service.h"
#include "taskconfig.h"


#include <WiFi.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>


/*Server connection -------------------*/
constexpr char THINGSBOARD_SERVER[] = "app.coreiot.io";
constexpr uint16_t THINGSBOARD_PORT = 1883U;

constexpr uint16_t MAX_MESSAGE_SEND_SIZE = 512U;
constexpr uint16_t MAX_MESSAGE_RECEIVE_SIZE = 512U;

void serverTask(void* pvParameters);
void initServerTask(void);



#endif // SERVER_TASK_H