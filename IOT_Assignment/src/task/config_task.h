#ifndef CONNECTION_TASK_H
#define CONNECTION_TASK_H
#pragma once

#include "service/web_ui_service.h"
#include "service/connection_service.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <Preferences.h>


void saveConfigToFlash(const config_data_t& config);
bool loadConfigFromFlash(config_data_t &config);
void clearConfigFromFlash();

void configTask(void* pvParameters);
void handlerResetTask(void* pvParameters);
void initConfigTask(void);




#endif // CONNECTION_TASK_H


