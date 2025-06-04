#ifndef SERVER_TASK_H
#define SERVER_TASK_H
#pragma once

#include "hal/module_sim.h"
#include "service/connection_service.h"
#include "taskconfig.h"

#include "service/rpc_handler_service.h"


void serverTask(void* pvParameters);
void initServerTask(void);



#endif // SERVER_TASK_H