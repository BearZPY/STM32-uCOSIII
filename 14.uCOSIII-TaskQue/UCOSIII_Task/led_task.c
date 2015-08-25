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
	u8 test[20];
	u8 times = 0;
	CPU_SR_ALLOC();
	u8 temp;	
	p_arg = p_arg;
	while(1)
	{
		OS_CRITICAL_ENTER();
		temp = isr_que.MsgQ.NbrEntriesSize - isr_que.MsgQ.NbrEntries;
		printf("que remain %d.\r\n",temp);
		OS_CRITICAL_EXIT();	
		sprintf((char *)test,"led_send_que %d",times++);
		printf("led0 task send que.\r\n");
		OSQPost((OS_Q*		)&isr_que,		
				(void*		)test,
				(OS_MSG_SIZE)20,
				(OS_OPT		)OS_OPT_POST_FIFO,
				(OS_ERR*	)&err);
				
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s	
			
	}
}


//		OS_CRITICAL_ENTER();
//		temp = isr_que.MsgQ.NbrEntriesSize - isr_que.MsgQ.NbrEntries;
//		printf("que remain %d.\r\n",temp);
//		OS_CRITICAL_EXIT();	
//		if(times == 5)
//		{
//			OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s
//			//printf("led0 task wait que .\r\n");
//			continue;
//		}
//		sprintf((char *)test,"led_send_que %d",times++);
//		printf("led0 task send que.\r\n");
//		OSQPost((OS_Q*		)&isr_que,		
//				(void*		)test,
//				(OS_MSG_SIZE)20,
//				(OS_OPT		)OS_OPT_POST_FIFO,
//				(OS_ERR*	)&err);
//				
//		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s	

