#include "stm32f10x.h"                  // Device header

extern uint16_t Num;

void Timer_Init()    //初始化定时器，步骤：RCC开启时钟，选择时基单元的时钟模式(内部是时钟源)，输出中断控制，配置NVIC，运行控制(使能计时器)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//RCC开启时钟
	
	TIM_InternalClockConfig(TIM2);//设置TIM2使用内部时钟，这一步可以不写
	
	TIM_TimeBaseInitTypeDef  TIM_BaseInitStructure;
	TIM_BaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //输入滤波装置分频使用的，可以随意配置
	TIM_BaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //选择向上计数的计数模式
	TIM_BaseInitStructure.TIM_Period= 10000 - 1 ;
	TIM_BaseInitStructure.TIM_Prescaler= 7200 - 1 ;//PSC预分频器的值，设置为7200即降到10Hz的频率  M就是10的6次方
	//配置时可以参照公式：CK_CNT_OV=72mHz/(PSC+1)/(ARR+!) 定时一秒就是定时频率为1Hz
	TIM_BaseInitStructure.TIM_RepetitionCounter= 0 ;//重复计数器的值，高级定时器才有
	TIM_TimeBaseInit(TIM2,&TIM_BaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);   //更新中断标志位手动清除
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//开启更新中断到NVIC的通路
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	
}

void TIM2_IRQHandler(void) //TIM2的中断函数
{
	//检查中断标志位
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
