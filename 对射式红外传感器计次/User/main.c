#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "CountSensor.h"
#include "Timer.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"


uint16_t Num;

int main()
{
	LED_Init();
	Buzzer_Init();
	LightSensor_Init();
	CountSensor_Init();
	OLED_Init();
	
	OLED_ShowString(1,1,"Count:");
	
	while(1)
	{
		LED1_ON();
		OLED_ShowNum(1,7,CountSensor_Get(),5);
		if(LightSensor_Get() == 1)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
	} 
}
