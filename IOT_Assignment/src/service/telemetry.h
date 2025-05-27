#ifndef TELEMETRY_H
#define TELEMETRY_H
#pragma one

#include <ArduinoJson.h>

extern DynamicJsonDocument data_document;

constexpr char KEY_SOIL_MOISTURE[] = "SoilMoisture";
constexpr char KEY_SOIL_TEMPERATURE[] = "SoilTemperature";
constexpr char KEY_WINDSPEAD[] = "WindSpeed";
constexpr char KEY_SOIL_PH[] = "SoilpH";
constexpr char KEY_SOIL_EC[] = "SoilEC";



#endif // TELEMETRY_H