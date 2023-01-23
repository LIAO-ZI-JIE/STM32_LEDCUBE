#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#define DataPin(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)(x))
#define ClockPin(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_1, (BitAction)(x))
#define LatchPin(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_2, (BitAction)(x))
uint8_t LED[8][8]=		{
						{0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
						{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
						{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
						{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
						{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
						{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
						{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
						{0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff},						
						};
void Cube_Init(void)
{
	Timer_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
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
//			DataPin=1;
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
  * @param   輸入的x (1~8)
  * @param   輸入的y (1~8)
  * @param   輸入的z (1~8)
  * @retval  無 
  */
void Cube_Draw(uint8_t x,uint8_t y,uint8_t z)
{
	LED[y-1][z-1]|=(0x01<<(x-1));
}