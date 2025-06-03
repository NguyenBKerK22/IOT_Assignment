#ifndef RPC_HANDLER_SERVICE_H
#define RPC_HANDLER_SERVICE_H
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "global.h"
#include "thingsboard.h"


void processGetRelayState(const JsonVariantConst &data, JsonDocument &response);
void processSetRelayState(const JsonVariantConst &data, JsonDocument &response);
void processSchedulerMorning(const JsonVariantConst &data, JsonDocument &response);
void processSchedulerAfternoon(const JsonVariantConst &data, JsonDocument &response);

/*one-shot task*/

void pumpTask(void* pvParameters);

#endif // RPC_HANDLER_SERVICE_H