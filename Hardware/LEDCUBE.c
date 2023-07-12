#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include <math.h>
#include <string.h>
#include "Delay.h"
#include "Matrix.h"
#define pi 3.1415926
#define DataPin(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_15, (BitAction)(x))
#define ClockPin(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)(x))
#define LatchPin(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_14, (BitAction)(x))
uint8_t LED[8][8];
void Cube_Init(void)
{
	Timer_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}
/**
  * @brief  將某一層的LED CUBE的數據輸出到LED CUBE
  * @param  stair輸入的層數0~7
  * @retval 無
  */
void Cube_Print (unsigned char stair)
{
	uint8_t i,j;
	DataPin(0);
	ClockPin(0);
	LatchPin(0);
	//輸出層的資料
	for(i=0;i<8;i++)
	{
		ClockPin(0);
		DataPin((0x80>>stair)&(0x01<<i));
		ClockPin(1);
		
	}
	//輸出燈的數據
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			ClockPin(0);
			DataPin((LED[stair][i])&(0x01<<j));
			ClockPin(1);
		}
	}
	LatchPin(1);
}
/**
  * @brief  將LED CUBE全部點亮
  * @param   無
  * @retval  無
  */
void Cube_Bright(void)
{
	uint8_t i,j;
	for (i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			LED[i][j]=0xff;
		}
	}
}
/**
  * @brief  將LED CUBE全部熄滅
  * @param   無
  * @retval  無
  */
void Cube_Dark(void)
{
	uint8_t i,j;
	for (i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			LED[i][j]=0x00;
		}
	}
}
/**
  * @brief   在LED CUBE上畫出點
  * @param   輸入的x座標 (0~7)
  * @param   輸入的y座標 (0~7)
  * @param   輸入的z座標 (0~7)
  * @retval  無 
  */
void Cube_Draw(int8_t x,int8_t y,int8_t z)
{
	if(x<0 || x>7 || y<0 || y>7 || z<0 || z>7)
	{
		return;
	}
	LED[z][y]|=(0x01<<(x));
}
/**
  * @brief 將波浪數據寫入
  * @param   無
  * @retval  無
  */
void Cube_Wave (void)
{
	int y,x,t;
    float z;
    for(t=0;t<14;t++)
    {
        for(y=0;y<8;y++)
        {
            for(x=0;x<8;x++)
            {
                z=3.5*sin((pi/7)*t+(pi/7)*x-(pi/7)*y)+4;
                Cube_Draw(x,y,z);
            }
        }
		Delay_ms(10);
		Cube_Dark();
    }   
}
void Cube_drawCube(int8_t x, int8_t y, int8_t z, int8_t s) 
{
  for (uint8_t i = 0; i < s; i++) {
    Cube_Draw(x, y + i, z);
    Cube_Draw(x + i, y, z);
    Cube_Draw(x, y, z + i);
    Cube_Draw(x + s - 1, y + i, z + s - 1);
    Cube_Draw(x + i, y + s - 1, z + s - 1);
    Cube_Draw(x + s - 1, y + s - 1, z + i);
    Cube_Draw(x + s - 1, y + i, z);
    Cube_Draw(x, y + i, z + s - 1);
    Cube_Draw(x + i, y + s - 1, z);
    Cube_Draw(x + i, y, z + s - 1);
    Cube_Draw(x + s - 1, y, z + i);
    Cube_Draw(x, y + s - 1, z + i);
  }
}
void Cube_DrawCube_Matrix(int8_t x, int8_t y, int8_t z, int8_t s,Matrix_Data *Matrix_Structure)
{
	static Matrix_Data last;
	if (memcmp(&last,Matrix_Structure,sizeof(last)))
    { 
		Cube_Dark();
		for (float i = 0; i < s; i++)
		{
		matrix_translate(x, y + i, z,Matrix_Structure);
		matrix_translate(x + i, y, z,Matrix_Structure);
		matrix_translate(x, y, z + i,Matrix_Structure);
		matrix_translate(x + s - 1, y + i, z + s - 1,Matrix_Structure);
		matrix_translate(x + i, y + s - 1, z + s - 1,Matrix_Structure);
		matrix_translate(x + s - 1, y + s - 1, z + i,Matrix_Structure);
		matrix_translate(x + s - 1, y + i, z,Matrix_Structure);
		matrix_translate(x, y + i, z + s - 1,Matrix_Structure);
		matrix_translate(x + i, y + s - 1, z,Matrix_Structure);
		matrix_translate(x + i, y, z + s - 1,Matrix_Structure);
		matrix_translate(x + s - 1, y, z + i,Matrix_Structure);
		matrix_translate(x, y + s - 1, z + i,Matrix_Structure);
		}
		memcpy(&last,Matrix_Structure,sizeof(last));
	}
}
