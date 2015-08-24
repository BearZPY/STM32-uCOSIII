#include "led_task.h"
#include "LED.h"
#include "sys.h"
#include "task.h"

//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

//led0任务函数
void led0_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		printf("led0 task use share_data, prio : %d\n\r",LED0_TASK_PRIO);
		sprintf((char*)share_data,"led0 task write.\n\r");
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时300ms
		
		printf("led0 task : %s",share_data);
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时300ms	
	}
}
