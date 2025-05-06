#include "global.h"
struct es_ws_02_data {
    int windSpeed; // Wind speed in m/s
};
struct es_ws_02 {
    es_ws_02_data data; // Data structure to hold wind speed data
    int pin; // Pin number for the sensor
    void begin(int pin) { // Function to initialize the sensor
        this->pin = pin;
        pinMode(pin, INPUT); // Set the pin as input
    }
    void readSensor() { // Function to read the sensor data
        data.windSpeed = analogRead(pin); // Read the analog value from the sensor
    }
    int getWindSpeed() { // Function to get the wind speed data
        return data.windSpeed; // Return the wind speed value
    }
};