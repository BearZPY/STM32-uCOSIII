#ifndef _FLOAT_TASK_H_
#define _FLOAT_TASK_H_


#include "includes.h"

//任务优先级
#define FLOAT_TASK_PRIO		6
//任务堆栈大小
#define FLOAT_STK_SIZE		128
//任务控制块
extern OS_TCB	FloatTaskTCB;
//任务堆栈
extern __align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];


void float_task(void *p_arg);
#endif
