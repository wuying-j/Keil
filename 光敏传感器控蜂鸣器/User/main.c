#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "CountSensor.h"
#include "Timer.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint16_t Num;

int main()
{
	LED_Init();
	Buzzer_Init();
	LightSensor_Init();
	while(1)
	{
		LED1_ON();
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
