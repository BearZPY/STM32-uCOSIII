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
	u8 test1[20] = "abcde";
	u8 test2[20] = "12345";
	u8 test3[20] = "45678";
	
	u8 times = 0;
	CPU_SR_ALLOC();
	u8 temp;	
	p_arg = p_arg;
	while(1)
	{
		OS_CRITICAL_ENTER();
		temp = FloatTaskTCB.MsgQ.NbrEntriesSize - FloatTaskTCB.MsgQ.NbrEntries;
		printf("que remain %d.\r\n",temp);
		OS_CRITICAL_EXIT();	
		sprintf((char *)test,"led_send_que %d",times++);
		printf("led0 task send que.\r\n");
		//消息队列传送的是地址 且不会进行数据拷贝
		//同一地址传输速度比处理任务快 会导致数据被覆盖 造成数据丢失
		//消息队列传送的是需要读取某个地址的次数
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//向任务Msgdis发送消息
					(void*		)test,
          (OS_MSG_SIZE)20,
          (OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//向任务Msgdis发送消息
					(void*		)&test1,
          (OS_MSG_SIZE)20,
          (OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//向任务Msgdis发送消息
					(void*		)&test2,
          (OS_MSG_SIZE)20,
          (OS_OPT		)OS_OPT_POST_FIFO,
					(OS_ERR*	)&err);
		OSTaskQPost((OS_TCB*	)&FloatTaskTCB,	//向任务Msgdis发送消息
					(void*		)&test3,
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

