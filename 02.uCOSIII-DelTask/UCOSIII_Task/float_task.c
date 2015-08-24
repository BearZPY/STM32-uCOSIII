#include "float_task.h"
#include "delay.h"
#include "uart.h"
#include "led_task.h"

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
				OSTaskDel((OS_TCB*)&Led0TaskTCB,&err);
				printf("删除LED任务\n\r");
		}
		if(float_num > 1.991f && float_num < 2.001f)
		{
				OS_CRITICAL_ENTER();	//进入临界区
				OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,		
					(CPU_CHAR	* )"led0 task", 		
							 (OS_TASK_PTR )led0_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )LED0_TASK_PRIO,     
							 (CPU_STK   * )&LED0_TASK_STK[0],	
							 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
							 (CPU_STK_SIZE)LED0_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,					
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
							 (OS_ERR 	* )&err);	
				printf("建立LED任务\n\r");
				OS_CRITICAL_EXIT();		//退出临界区
				float_num = 0.0f;
		}
		OSTimeDlyHMSM(0,0,0,300,OS_OPT_TIME_HMSM_STRICT,&err); //延时300ms
		
	}
}
