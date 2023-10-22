#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "CountSensor.h"
#include "Timer.h"

uint16_t Num;

int main()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
 	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
//	GPIO_SetBits(GPIOA,GPIO_Pin_0);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	while(1)
	{
		GPIO_Write(GPIOA,~0x0001);  //0000 0000 0000 0001  低电平点亮，在前面加一个按位取反的~
		Delay_ms(500);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_Write(GPIOA,~0x0002);  //0000 0000 0000 0010  
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0004);  //0000 0000 0000 0100 
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0008);  //0000 0000 0000 1000 
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0010);  //0000 0000 0001 0000 
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0020);  //0000 0000 0010 0000
		Delay_ms(500);
		GPIO_Write(GPIOA,~0x0040);  //0000 0000 0100 0000
		Delay_ms(500);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		Delay_ms(500);
	} 
}
