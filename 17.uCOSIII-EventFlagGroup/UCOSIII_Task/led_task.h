#ifndef LED_TASK_H_
#define LED_TASK_H_


#include "includes.h"

//任务优先级
#define LED0_TASK_PRIO		5u
//任务堆栈大小	
#define LED0_STK_SIZE 		128u
//任务控制块
extern OS_TCB Led0TaskTCB;
//任务堆栈	
extern CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

void led0_task(void *p_arg);

#endif
