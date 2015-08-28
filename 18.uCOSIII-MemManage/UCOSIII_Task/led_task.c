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
	CPU_INT08U *buf;
	p_arg = p_arg;
	while(1)
	{
		buf = OSMemGet((OS_MEM*)&my_mem,
								      (OS_ERR*)&err);
		if(err == OS_ERR_NONE) //内存申请成功
		{
			printf("led0 task get mem \n\r");
		}
		
		if(err == OS_ERR_MEM_NO_FREE_BLKS) //内存申请成功
		{
			printf("No Free Mem \n\r");
		}	
					
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s	
		OSMemPut((OS_MEM*	)&my_mem,		//释放内存
					 (void*		)buf,
					 (OS_ERR* 	)&err);
		printf("buf内存释放之后的地址为:%#x\r\n",(u32)(buf));
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s	
	
	}
}


