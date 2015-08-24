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
	//CPU_SR_ALLOC();
	while(1)
	{
		printf("float task wait Mutex Sem to Sync. \n\r");
		// 请求信号量
		//OSMutexPend(&Mutex_Sem,0,OS_OPT_PEND_BLOCKING,0,&err);
		OSSemPend(&SYNC_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); //请求信号量
		
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //延时300ms	
		printf("float task get sem \n\r");
		//OSMutexPost(&Mutex_Sem,OS_OPT_POST_ALL,&err);
	}
}
