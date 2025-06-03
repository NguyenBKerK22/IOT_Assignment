#ifndef THINGSBOARD_H
#define THINGSBOARD_H
#pragma once

#include "global.h"

/* Server info */
constexpr char THINGSBOARD_SERVER[] = "app.coreiot.io";
constexpr uint16_t THINGSBOARD_PORT = 1883U;

constexpr uint16_t MAX_MESSAGE_SEND_SIZE = 512U;
constexpr uint16_t MAX_MESSAGE_RECEIVE_SIZE = 512U;

constexpr uint8_t MAX_RPC_SUBSCRIPTIONS = 5U;
constexpr uint8_t MAX_RPC_RESPONSE = 10U;

/* RPC method names */
constexpr const char RPC_SET_RELAY_METHOD[] = "setRelayStatus";
constexpr const char RPC_GET_RELAY_METHOD[] = "getRelayStatus";
constexpr const char SCHEDULER_TURNON_MORNING_METHOD[] = "turnOnSchedulerMorning";
constexpr const char SCHEDULER_TURNON_AFTERNOON_METHOD[] = "turnOnSchedulerAfternoon";


/* Telemetry key */
constexpr char KEY_HUMIDITY[] = "Humidity";
constexpr char KEY_TEMPERATURE[] = "Temperature";
constexpr char KEY_WINDSPEAD[] = "WindSpeed";
constexpr char KEY_LIGHT_AMBIENT[] = "AmbientLight";

/* extern biến toàn cục */
extern ThingsBoard *tb;
extern Arduino_MQTT_Client *mqttClient;
extern Server_Side_RPC<MAX_RPC_SUBSCRIPTIONS, MAX_RPC_RESPONSE> rpc;
extern const std::array<IAPI_Implementation*, 1U> apis;

#endif // THINGSBOARD_H
