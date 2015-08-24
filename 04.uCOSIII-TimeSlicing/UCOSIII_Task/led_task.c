#include "led_task.h"
#include "LED.h"
#include "sys.h"

//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

//led0任务函数
void led0_task(void *p_arg)
{
	OS_ERR err;
	uint32_t temp = 0;
	uint8_t i = 0;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	while(1)
	{	
		OS_CRITICAL_ENTER();	//进入临界区
		printf("LED run %d times\r\n",temp++);
		OS_CRITICAL_EXIT();	//进入临界区
		
		for( i = 0;i < 5; i++ )
			printf("LED : 12345 \r\n");
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err);
	}
}

//		printf("LED 运行 %d 次\r\n",temp++);
//		LED0 = 0;
//		OSTimeDlyHMSM(0,0,0,300,OS_OPT_TIME_HMSM_STRICT,&err); //延时200ms
//		LED0 = 1;
//		OSTimeDlyHMSM(0,0,0,300,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
