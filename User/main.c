#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LEDCUBE.h"
#include "Matrix.h"
					
int main(void)
{

	Cube_Init();
	Cube_Dark();
																									


	while (1)
	{
		Matrix_Data Matrix_structure;
		Matrix_structure.X_rotation=0;
		Matrix_structure.Y_rotation=0;
		Matrix_structure.Z_rotation=90;
		Matrix_structure.X_translation=0;
		Matrix_structure.Y_translation=0;
		Matrix_structure.Z_translation=0;
		Matrix_structure.X_scale=1;
		Matrix_structure.Y_scale=1;
		Matrix_structure.Z_scale=1;
		matrix_translate(2,0,0,&Matrix_structure);
//		Cube_Wave();
	}
	

		
		

	
}
void TIM2_IRQHandler(void)
{
	static uint8_t stair;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		if(stair>7){stair=0;}
		Cube_Print(stair);
		stair++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
