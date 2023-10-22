#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "CountSensor.h"
#include "OLED.h"
int main()
{
	OLED_Init();
	
	CountSensor_Init();

	while(1)
	{
		
	}
}
