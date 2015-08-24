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
	CPU_SR_ALLOC();
	static float float_num = 0.01;
	//uint32_t temp = &float_num;
	while(1)
	{
		float_num+=0.01f;
		OS_CRITICAL_ENTER();	//进入临界区
		printf("float_num的值为: %.4f\r\n",float_num);
		OS_CRITICAL_EXIT();		//退出临界区
		if(float_num > 0.901f && float_num < 0.919f)
		{
				OSTaskSuspend((OS_TCB*)&Led0TaskTCB,&err);
				printf("挂起LED任务\n\r");
		}
		if(float_num > 1.991f && float_num < 2.001f)
		{
				OSTaskResume((OS_TCB*)&Led0TaskTCB,&err);
				printf("恢复LED任务\n\r");
				float_num = 0.0f;
		}
		OSTimeDlyHMSM(0,0,0,300,OS_OPT_TIME_HMSM_STRICT,&err); //延时300ms	
	}
}
