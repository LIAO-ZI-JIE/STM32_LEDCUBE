#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Matrix.h"
#include "Serial.h"	
#include "LEDCUBE.h"
int main(void)
{
	Cube_Init();
	Cube_Dark();
	Serial_Init();
	printf("the command is:\r\n");
	printf("@+123Matrix_Translate_X_Data$\r\n");
	printf("@+123Matrix_rotation_Y_Data$\r\n");
	printf("@+123Matrix_scale_Z_Data$\r\n");
	Matrix_Data Matrix_structure;
	Matrix_structure.X_rotation=0;
	Matrix_structure.Y_rotation=0;
	Matrix_structure.Z_rotation=0;
	Matrix_structure.X_translation=0;
	Matrix_structure.Y_translation=0;
	Matrix_structure.Z_translation=0;
	Matrix_structure.X_scale=1;
	Matrix_structure.Y_scale=1;
	Matrix_structure.Z_scale=1;

	while (1)
	{

		if (Serial_RxFlag == 1)
		{
			Serial_Change(&Matrix_structure);			
			Serial_RxFlag = 0;
		}
		Cube_DrawCube_Matrix(0,0,0,3,&Matrix_structure);
		
//		i++;
//		

//		printf("hello%d\r\n",i);

//		matrix_translate(2,0,0,&Matrix_structure);
//		Cube_Wave();
//		Cube_Bright();
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
