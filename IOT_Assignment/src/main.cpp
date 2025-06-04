#include "global.h"
#include "task/config_task.h"
#include "task/server_task.h"
#include "task/modbus_sensor.h"

void setup() {  
  Serial.begin(9600);  
  pinMode(PUMP, OUTPUT);
  pinMode(FOGGER, OUTPUT);
  pinMode(AWNING, OUTPUT);

  
  initServerTask();
  initConfigTask();  
  initModbusTasks();

  
}

void loop() {  
  
}