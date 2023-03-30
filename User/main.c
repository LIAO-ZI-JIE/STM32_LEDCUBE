#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LEDCUBE.h"

int16_t Data[10][4]=
					{
						{-2,1,1,0},
						{-2,2,1,0},
						{-1,1,1,0},	
						{-1,2,1,0},
						{0,1,1,0},	
						{0,2,1,0},
						{1,1,1,0},
						{1,2,1,0},
						{2,1,1,0},
						{2,2,1,0},
					};
int16_t Matrix_x[4][4]= {
						{1,0,0,4},
						{0,0,-1,-4},
						{0,1,0,3},
						{0,0,0,1}
						};
int16_t Matrix_m[4][4]= {
						{1,0,0,4},
						{0,1,0,4},
						{0,0,1,3},
						{0,0,0,1}
						};
int16_t NewData[1][4]=
					{
						0,0,0,0,
					
					};
int16_t outData[1][4]={0,0,0,0};
					
int main(void)
{

	Cube_Init();
	Cube_Dark();
	Cube_Draw(0,0,0);
//	Cube_Draw(8,8,1);

	while (1)
	{
//		
		uint8_t x,y,z,i,j,k;
//		
////		for(x=0;x<10;x++)
////		{
////			for(j=0;j<4;j++)
////			{
////				NewData[1][j]=Data[i][j];
////			}
////			i = 0;//行
////			j = 0;//列
////			k = 0;//行列中，第k个元素相乘
////			for (i = 0; i < 4; i++)//从第i行开始
////			{
////				for (j = 0; j < 1; j++)//从第j列开始
////				{
////					for (k = 0; k < 4; k++)//i行元素和j列元素相乘，结果累加
////					{
////						outData[i][j] += Matrix_m[i][k] * NewData[k][j];
////					}
////				}
////			}
////						
////				Cube_Draw(outData[0][0],outData[0][1],outData[0][2]);

////		}

////			Cube_Draw(Data[x][0]+4,Data[x][1]+4,Data[x][2]+4);
//		Cube_Dark();
//		for(x=1;x<=8;x++)
//		{
//			for(y=1;y<=8;y++)
//			{
//				for(z=1;z<=8;z++)
//				{
//						Cube_Draw(x,y,z);
//						Delay_ms(10);
//				}
//			
//			}
//		
//		}
//		Cube_Dark();
//		for(y=1;y<=8;y++)
//		{
//			for(x=1;x<=8;x++)
//			{
//				for(z=1;z<=8;z++)
//				{
//						Cube_Draw(x,y,z);
//						Delay_ms(10);
//				}
//			
//			}
//		
//		}
//		Cube_Dark();
//		for(z=1;z<=8;z++)
//		{
//			for(x=1;x<=8;x++)
//			{
//				for(y=1;y<=8;y++)
//				{
//						Cube_Draw(x,y,z);
//						Delay_ms(1000);
//				}
//			
//			}
//		
//		}
		

//	for (uint8_t i = 0; i < s; i++) {
//    Cube_Draw(x, y + i, z);
//    Cube_Draw(x + i, y, z);
//    Cube_Draw(x, y, z + i);
//    Cube_Draw(x + s - 1, y + i, z + s - 1);
//    Cube_Draw(x + i, y + s - 1, z + s - 1);
//    Cube_Draw(x + s - 1, y + s - 1, z + i);
//    Cube_Draw(x + s - 1, y + i, z);
//    Cube_Draw(x, y + i, z + s - 1);
//    Cube_Draw(x + i, y + s - 1, z);
//    Cube_Draw(x + i, y, z + s - 1);
//    Cube_Draw(x + s - 1, y, z + i);
//    Cube_Draw(x, y + s - 1, z + i);
//  }
		Cube_Wave();
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
