#include "LED.h"
#include "sys.h"
#include "stm32f10x.h"                  // Device header


void LED_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);	 //使能PG端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC端口时钟
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //LED0-->PG15 端口配置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		  			//LED0-->PC13 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	//GPIO_SetBits(GPIOG,GPIO_Pin_15);		
}
