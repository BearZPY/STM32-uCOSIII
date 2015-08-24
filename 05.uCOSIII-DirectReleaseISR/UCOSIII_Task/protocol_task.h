#ifndef _PROTOCOL_TASK_H_
#define _PROTOCOL_TASK_H_

#include "includes.h"

//任务优先级
#define Protocol_TASK_PRIO		4u
//任务堆栈大小	
#define Protocol_STK_SIZE 		128u
//任务控制块
extern OS_TCB ProtocolTaskTCB;
//任务堆栈	
extern CPU_STK Protocol_TASK_STK[Protocol_STK_SIZE];

void protocol_task(void *p_arg);


#endif

