#include "button.h"

uint8_t is_pressed = 0;
uint8_t data0, data1, data2, oldDataStable, dataStable;

void deboucing_run(){
    data2 = data1;
    data1 = data0;
    data0 = digitalRead(BUTTON_PIN);
    if(data0 == data1 && data1 == data2){
      oldDataStable = dataStable;
      dataStable = data0;
      if(oldDataStable == 0 && dataStable == 1){
        is_pressed = 1;
      };
    };
};

uint8_t get_button_state(){
    return is_pressed;
};
