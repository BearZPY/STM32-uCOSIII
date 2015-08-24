#ifndef START_TASK_H_
#define START_TASK_H_


#include "includes.h"

//任务优先级
#define START_TASK_PRIO		3u
//任务堆栈大小	
#define START_STK_SIZE 		512u
//任务控制块
extern OS_TCB StartTaskTCB;
//任务堆栈	
extern CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);


#endif
