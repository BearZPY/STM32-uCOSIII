#include "float_task.h"
#include "delay.h"
#include "uart.h"
#include "task.h"

//任务控制块
OS_TCB	FloatTaskTCB;
//任务堆栈
__align(8) CPU_STK	FLOAT_TASK_STK[FLOAT_STK_SIZE];

//浮点测试任务
void float_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		printf("mem  free block %d \n\r",my_mem.NbrFree);
		
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //延时800ms	
	}
}
