#ifndef _TASK_H_
#define _TASK_H_

#include "start_task.h"

#include "led_task.h"

#include "float_task.h"

#include "protocol_task.h"


extern int8_t share_data[20]; 
extern OS_SEM sem_share_data;

#endif
