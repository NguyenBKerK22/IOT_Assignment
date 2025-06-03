#include <Arduino.h>
#include "task/config_task.h"
#include "task/server_task.h"






void setup() {
  Serial.begin(9600);  

  initServerTask();
  delay(100);
  initConfigTask();
  
}

void loop() {  
  
}