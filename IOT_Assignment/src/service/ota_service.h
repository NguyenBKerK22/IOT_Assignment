#ifndef OTA_SERVICE_H
#define OTA_SERVICE_H
#pragma once 

#include <stdlib.h>
#include <Arduino.h>


void update_starting_callback();
void finished_callback(const bool & success);
void progress_callback(const size_t & current, const size_t & total);


#endif // OTA_SERVICE_H