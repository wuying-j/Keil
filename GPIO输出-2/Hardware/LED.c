#include"stm32f10x.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode= GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin= GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3);
}   //LED的GPIO口的初始化函数，可以根据提示写

void LED1_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}
