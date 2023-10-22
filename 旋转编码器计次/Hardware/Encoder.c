#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//EXTI不需要开启时钟
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//配置AFIO外部中断引脚选择
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);//GPIOB的0号引脚
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);//GPIO的1号引脚
	//配置EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC， NVIC的库函数在misc里面
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//用来中断分组的函数,整个代码只需要配置一次进行分组
	NVIC_InitTypeDef NVIC_InitSTructure;
	NVIC_InitSTructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitSTructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSTructure.NVIC_IRQChannelPreemptionPriority= 1;//此时中断只有一个，随意配置
	NVIC_InitSTructure.NVIC_IRQChannelSubPriority= 1;
	NVIC_Init(&NVIC_InitSTructure);
	
	NVIC_InitSTructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitSTructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSTructure.NVIC_IRQChannelPreemptionPriority= 1;//此时中断只有一个，随意配置
	NVIC_InitSTructure.NVIC_IRQChannelSubPriority= 2;
	NVIC_Init(&NVIC_InitSTructure);
}

int16_t Encoder_Get(void)
{
	int16_t temp;
	temp=Encoder_Count;
	Encoder_Count=0;
	return temp;
}



void EXTI0_IRQHandler(void)
//正向旋转时，下降沿触发的波形B会比A早半个相位，检测到A下降沿触发时，B为低电平时判断为反转，反转执行--
{
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)//判断接1口的B是否为低电平，判断是否为反转
		{
			Encoder_Count--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
//正向旋转时，下降沿触发的波形B会比A晚半个相位，检测到B向下降沿触发，A为低电平时判断为正转，正转就执行++
{
	if(EXTI_GetITStatus(EXTI_Line1)==SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)//判断接0口的A是否为低电平，判断时否为正转
		{
			Encoder_Count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
