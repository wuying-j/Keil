#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "CountSensor.h"
#include "OLED.h"
#include "Timer.h"

uint16_t Num;

int main()
{
	OLED_Init();
	
	OLED_ShowString(1,1,"Num:");
	
	while(1)
	{
		OLED_ShowNum(1,5,Num,5);
	}
}
