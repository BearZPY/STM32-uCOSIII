#include "protocol_task.h"
#include "task.h"
#include "uart.h"
#include "led.h"

//任务控制块
OS_TCB ProtocolTaskTCB;
//任务堆栈	
CPU_STK Protocol_TASK_STK[Protocol_STK_SIZE];

	
void protocol_task(void *p_arg)
{
	OS_ERR err;
	static uint8_t Date_Handle_Flag = 0;
	uint8_t temp = 0;
	p_arg = p_arg;
	while(1)
	{
		
		OSTaskSemPend(0,OS_OPT_PEND_BLOCKING,0,&err);	
		if( !Date_Handle_Flag)  //Uart3_Recv_STA &&
		{
			Date_Handle_Flag = 1;
			//Uart3_Recv_STA = 0;
		}
		if(Date_Handle_Flag)
		{
			temp = Hekr_RecvData_Handle(Uart3_Recv_Buffer);
			if(Valid_Data_Update == temp)
			{
				//接收的数据保存在 Valid_Data 数组里
				//User Code
				if(Valid_Data[0] == 0x01)
				{
					LED0 = 1;
					OSTaskSuspend((OS_TCB*)&Led0TaskTCB,&err);
					printf("挂起LED任务\n\r");	
				}
				else
				{
					LED0 = 0;
					OSTaskResume((OS_TCB*)&Led0TaskTCB,&err);
					printf("恢复LED任务\n\r");	
				}
//				if(Valid_Data[1] == 0x01)
//				{
//					OSTaskDel((OS_TCB*)&FloatTaskTCB,&err);
//					printf("删除float任务\n\r");	
//				}
//				else
//				{
//										//创建浮点测试任务
//						OSTaskCreate((OS_TCB 	* )&FloatTaskTCB,		
//									 (CPU_CHAR	* )"float test task", 		
//													 (OS_TASK_PTR )float_task, 			
//													 (void		* )0,					
//													 (OS_PRIO	  )FLOAT_TASK_PRIO,     	
//													 (CPU_STK   * )&FLOAT_TASK_STK[0],	
//													 (CPU_STK_SIZE)FLOAT_STK_SIZE/10,	
//													 (CPU_STK_SIZE)FLOAT_STK_SIZE,		
//													 (OS_MSG_QTY  )0,					
//													 (OS_TICK	  )0,					
//													 (void   	* )0,				
//													 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, 
//													 (OS_ERR 	* )&err);		
//				}
			}
			if(Hekr_Module_State_Update == temp)
			{
				//接收的数据保存在 Module_Status 数组里
				//User Code
			}
			Date_Handle_Flag = 0;		
		}
		OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_HMSM_STRICT,&err); //延时10ms
	}
}
