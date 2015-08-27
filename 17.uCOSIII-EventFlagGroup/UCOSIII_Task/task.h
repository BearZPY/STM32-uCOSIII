#ifndef _TASK_H_
#define _TASK_H_

#include "start_task.h"

#include "led_task.h"

#include "float_task.h"

#include "protocol_task.h"

extern OS_FLAG_GRP event_flag;

#define FLAG_BIT(n)  1<<n

#endif
