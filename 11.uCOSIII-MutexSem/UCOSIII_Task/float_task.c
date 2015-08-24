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
		OSTimeDlyHMSM(0,0,0,400,OS_OPT_TIME_HMSM_STRICT,&err); //延时400ms	
		printf("float task wait Mutex Sem . \n\r");
		// 请求信号量
		OSMutexPend(&Mutex_Sem,0,OS_OPT_PEND_BLOCKING,0,&err);
		//OSSemPend(&SYNC_SEM,0,OS_OPT_PEND_BLOCKING,0,&err); //请求信号量
		printf("float task get Mutex Sem \n\r");
		OSMutexPost(&Mutex_Sem,OS_OPT_POST_NO_SCHED,&err);
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); //延时100ms	
	}
}
