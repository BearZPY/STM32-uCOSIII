#ifndef _UART3_H_
#define _UART3_H_

#include "stm32f10x.h"                  // Device header
#include "hekr_protocol.h"

extern u8 Uart3_Recv_Buffer[20];
extern u8 Uart3_Recv_Count;
extern u8 Uart3_Recv_STA;


void Uart3_init(void);
void UART3_SendChar(u8 ch);

#endif

