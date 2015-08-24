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
		// 请求信号量
		OSSemPend(&sem_share_data,0,OS_OPT_PEND_BLOCKING,0,&err);
		printf("float task use share_data, prio : %d\n\r",FLOAT_TASK_PRIO);
		
		sprintf((char*)share_data,"float task write.\n\r");
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时300ms

		printf("float task : %s",share_data);		
		// 发送信号量
		OSSemPost(&sem_share_data,OS_OPT_POST_1,&err);
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时300ms	
	}
}
