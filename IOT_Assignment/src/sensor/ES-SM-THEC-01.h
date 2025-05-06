#include "global.h"
struct es_sm_thec_01_data {
  float temperature_value; // Temperature in Celsius
  float humidity_value; // Humidity in percentage
  float electrical_value; // Pressure in hPa
};
struct es_sm_thec_01 {
    es_sm_thec_01_data data; // Data structure to hold temperature, humidity, and pressure data
    int pin; // Pin number for the sensor
    void begin(int pin) { // Function to initialize the sensor
        this->pin = pin;
        pinMode(pin, INPUT); // Set the pin as input
    }
    void readSensor() { // Function to read the sensor data
        data.temperature_value = analogRead(pin); // Read the analog value from the sensor for temperature
        data.humidity_value = analogRead(pin); // Read the analog value from the sensor for humidity
        data.electrical_value = analogRead(pin); // Read the analog value from the sensor for pressure
    }
    float getTemperature() { // Function to get the temperature data
        return data.temperature_value; // Return the temperature value
    }
    float getHumidity() { // Function to get the humidity data
        return data.humidity_value; // Return the humidity value
    }
    float getPressure() { // Function to get the pressure data
        return data.electrical_value; // Return the pressure value
    }
};