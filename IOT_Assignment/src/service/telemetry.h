#ifndef TELEMETRY_H
#define TELEMETRY_H
#pragma once

#include <ArduinoJson.h>

extern DynamicJsonDocument data_document;

constexpr char KEY_HUMIDITY[] = "Humidity";
constexpr char KEY_TEMPERATURE[] = "Temperature";
constexpr char KEY_WINDSPEAD[] = "WindSpeed";
constexpr char KEY_LIGHT_AMBIENT[] = "AmbientLight";



#endif // TELEMETRY_H