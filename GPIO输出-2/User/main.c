#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "CountSensor.h"
#include "Timer.h"
#include "Key.h"

uint8_t KeyNum;
uint16_t Num;

int main()
{
	LED_Init();
	Key_Init();
	
//	GPIO_SetBits(GPIOA,GPIO_Pin_0);
//	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//	GPIO_WriteBit(GPIOA,GPIO_Pin_0,Bit_RESET);
	while(1)
	{
//		GPIO_Write(GPIOA,~0x0002);  //0000 0000 0000 0010  
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0004);  //0000 0000 0000 0100 
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0008);  //0000 0000 0000 1000 
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0010);  //0000 0000 0001 0000 
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0020);  //0000 0000 0010 0000
//		Delay_ms(500);
//		GPIO_Write(GPIOA,~0x0040);  //0000 0000 0100 0000
//		Delay_ms(500);
//		GPIO_SetBits(GPIOA,GPIO_Pin_0);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
//		Delay_ms(500);
//		GPIO_SetBits(GPIOB,GPIO_Pin_12);
//		Delay_ms(500);
		KeyNum = Key_GetNum() ;
		if(KeyNum == 1)
		{
			LED1_ON();
			LED2_OFF();
			
		}
		if(KeyNum == 2)
		{
			LED1_OFF();
			LED2_ON();
		}
	} 
}
