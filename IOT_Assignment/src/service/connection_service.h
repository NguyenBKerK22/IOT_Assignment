#ifndef CONNECTION_SERVICE_H
#define CONNECTION_SERVICE_H
#pragma once

#include "hal/module_sim.h"
#include <WiFi.h>
#include "web_ui_service.h"

#define CONNECTION_TIMEOUT 5000

typedef enum {
    timeout_wifi = 0,
    timeout_4G = 1,
    connected_wifi = 2,
    connected_4G = 3
} logger_connection_t;

logger_connection_t initConnection(config_data_t device_config_data);
void clearConfiguration(void);


#endif // CONNECTION_SERVICE_H