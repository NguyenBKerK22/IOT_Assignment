#include "global.h"
#include "task/config_task.h"
#include "task/server_task.h"







void setup() {  
  Serial.begin(9600);  
  pinMode(PUMP, OUTPUT);
  pinMode(FOGGER, OUTPUT);
  pinMode(AWNING, OUTPUT);

  initServerTask();  
  initConfigTask();
  
}

void loop() {  
  
}