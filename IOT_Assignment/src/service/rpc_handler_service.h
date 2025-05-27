#ifndef RPC_HANDLER_SERVICE_H
#define RPC_HANDLER_SERVICE_H
#pragma one

#include <stdlib.h>
#include <ArduinoJson.h>

constexpr const char RPC_SET_RELAY_METHOD[] = "setRelaytStatus";
constexpr const char RPC_GET_RELAY_METHOD[] = "getRelayStatus";
constexpr uint8_t MAX_RPC_SUBSCRIPTIONS = 2U;
constexpr uint8_t MAX_RPC_RESPONSE = 2U;

void processGetRelayState(const JsonVariantConst &data, JsonDocument &response);
void processSetRelayState(const JsonVariantConst &data, JsonDocument &response);

#endif // RPC_HANDLER_SERVICE_H