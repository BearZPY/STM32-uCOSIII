#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"                  // Device header

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);


#endif

