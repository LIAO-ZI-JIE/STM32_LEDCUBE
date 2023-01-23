#include "stm32f10x.h"                  // Device header
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//濾波器時鐘選擇
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//計數器模式
	TIM_TimeBaseInitStructure.TIM_Period=10-1;//ARR計數
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;//預分頻器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重複計數器
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);//因為Timebase會觸發中斷,清除中斷
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//使能中斷

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);

}

/*
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/
