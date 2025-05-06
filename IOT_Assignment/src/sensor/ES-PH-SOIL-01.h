#include "global.h"
struct es_ph_soil_01_data {
  int PH_value;
};
struct es_ph_soil_01 {
    es_ph_soil_01_data data; // Data structure to hold pH value
    int pin; // Pin number for the sensor
    void begin(int pin) { // Function to initialize the sensor
        this->pin = pin;
        pinMode(pin, INPUT); // Set the pin as input
    }
    void readSensor() { // Function to read the sensor data
        data.PH_value = analogRead(pin); // Read the analog value from the sensor
    }
    int getPH() { // Function to get the pH value
        return data.PH_value; // Return the pH value
    }
};