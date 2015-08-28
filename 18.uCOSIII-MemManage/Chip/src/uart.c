#include "uart.h"
#include "stdio.h"
#include "includes.h"					//ucos 使用	  
#include "task.h"


u8 Uart3_Recv_Buffer[20];
u8 Uart3_Recv_Count = 0;
u8 Uart3_Recv_STA = 0;


void Uart3_init(void)
{
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3，GPIOB时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//USART3_TX   GPIOB.10
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB.10
   
  //USART3_RX	  GPIOB.11初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PB11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = 9600;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART3, &USART_InitStructure); //初始化串口3
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART3, ENABLE);                    //使能串口3
	
	
//	BSP_IntVectSet(BSP_INT_ID_USART3,(CPU_FNCT_VOID)Recv_Protocol);
//	BSP_IntPrioSet(BSP_INT_ID_USART3,1);   
//	BSP_IntEn(BSP_INT_ID_USART3); 
}



void USART3_IRQHandler(void)
{
	
	if(0 == OSRunning)
		return ;
	OSIntEnter();
	//BSP_IntHandlerUSART3();
	Recv_Protocol();
	OSIntExit();
}

void Recv_Protocol(void)
{
	u8 ch;
	OS_ERR err;
	static u8 temp_flag = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
	{
		ch =USART_ReceiveData(USART3);
		if(ch == Hekr_Frame_Header)
		{
			temp_flag = 1;
			Uart3_Recv_Count = 0;
		}
		if(temp_flag)
		{
			Uart3_Recv_Buffer[Uart3_Recv_Count++] = ch;
			if(Uart3_Recv_Count > 4 && Uart3_Recv_Count >= Uart3_Recv_Buffer[1])
			{
				//Uart3_Recv_STA = 1;
				OSTaskSemPost(&ProtocolTaskTCB,OS_OPT_POST_NONE,&err);
				temp_flag = 0;
				Uart3_Recv_Count = 0;
			}
//			if(Uart3_Recv_Count > 15)
//			{
//				temp_flag = 0;
//				Uart3_Recv_Count = 0;
//			}
		}
	}	
}

void UART3_SendChar(u8 ch)
{
	while((USART3->SR&0X40)==0);//循环发送,直到发送完毕   
    USART3->DR = (u8) ch; 
}

int fputc(int ch, FILE *f)
{
	UART3_SendChar(ch);
	return ch;
}
