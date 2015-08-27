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
	OS_MSG_SIZE size;
	char *p;
	//CPU_SR_ALLOC();
	while(1)
	{
		p=OSTaskQPend((OS_TICK		)0,
                      (OS_OPT		)OS_OPT_PEND_BLOCKING,
                      (OS_MSG_SIZE*	)&size,
                      (CPU_TS*		)0,
                      (OS_ERR*      )&err );
		
		printf("float task get  que . \n\r");
		printf("que:  %s. \n\r",p);
		
		OSTimeDlyHMSM(0,0,1,800,OS_OPT_TIME_HMSM_STRICT,&err); //延时800ms	
	}
}
