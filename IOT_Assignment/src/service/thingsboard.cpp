#include "thingsboard.h"

/* Định nghĩa các biến toàn cục */
ThingsBoard *tb = nullptr;
Arduino_MQTT_Client *mqttClient = nullptr;

Server_Side_RPC<MAX_RPC_SUBSCRIPTIONS, MAX_RPC_RESPONSE> rpc;
const std::array<IAPI_Implementation*, 1U> apis = {
    &rpc
};
