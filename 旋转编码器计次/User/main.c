#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "CountSensor.h"
#include "Timer.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "OLED.h"
#include "Encoder.h"

int16_t Num;

int main()
{
	
	Encoder_Init();
	
	OLED_Init();
	OLED_ShowString(1,1,"Num:");
	
	while(1)
	{
		Num+=Encoder_Get();
		OLED_ShowNum(1,5,Num,5);
		LED1_ON();
		if(LightSensor_Get() == 1)
		{
			
		}
		else
		{
			Buzzer_OFF();
		}
	} 
}
