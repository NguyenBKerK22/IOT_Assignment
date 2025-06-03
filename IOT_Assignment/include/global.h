#include <WiFi.h>
#include <ThingsBoard.h>
#include <Arduino_MQTT_Client.h>
#include <Server_Side_RPC.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <array>

#include <Preferences.h>

#define PUMP 26
#define FOGGER 33
#define AWNING 32
