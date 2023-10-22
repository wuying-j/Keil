#include<stm32f10x.h>    //Device header


uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	//中断输入到CPU过程：GPIO->EXTI->NVIC->CPU
	//配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//EXTI不需要开启时钟
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置AFIO外部中断引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//GPIOB的14号引脚

	//配置EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC， NVIC的库函数在misc里面
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//用来中断分组的函数,整个代码只需要配置一次进行分组
	NVIC_InitTypeDef NVIC_InitSTructure;
	NVIC_InitSTructure.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVIC_InitSTructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSTructure.NVIC_IRQChannelPreemptionPriority= 1;//此时中断只有一个，随意配置
	NVIC_InitSTructure.NVIC_IRQChannelSubPriority= 1;
	NVIC_Init(&NVIC_InitSTructure);
	
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)//定义中断函数，函数名一般都是给定的，自己找
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
}

