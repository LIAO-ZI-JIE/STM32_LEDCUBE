#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "Matrix.h"
#include <stdio.h>
uint8_t Serial_RxData;
uint8_t Serial_RxFlag;
char Serial_RxPacket[100];
char *Matrix_Serial_Command[]={
    "Matrix_Translate_X_Data",
    "Matrix_Translate_Y_Data",
    "Matrix_Translate_Z_Data",
    "Matrix_rotation_X_Data",
    "Matrix_rotation_Y_Data",
    "Matrix_rotation_Z_Data",
    "Matrix_scale_X_Data",
    "Matrix_scale_Y_Data",
    "Matrix_scale_Z_Data",
    };

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	 
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;//鮑率
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//流控
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx ;//串口模式(輸入或輸出)
	USART_InitStructure.USART_Parity=USART_Parity_No;//數據較驗位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;//停止位長度
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;//數據長度
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//開啟接收中斷
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for(i=0;String[i] != '\0';i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result = 1;
	while (Y --)
	{
		Result *= X;
	}
	return Result;
}
void Serial_SendNum(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
	Serial_SendByte(Number/Pow(10,Length-i-1)%10+'0');
	}
}



uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}


void Serial_Change(Matrix_Data *Matrix_Structure)
{
    int32_t Num;
    int8_t i;
    char *Serial_Data_point=Serial_RxPacket;
    Num=(int)(Serial_RxPacket[1]-'0')*100+(int)(Serial_RxPacket[2]-'0')*10+(int)(Serial_RxPacket[3]-'0');
    if(Serial_RxPacket[0]=='-')
    {
        Num=-Num;
    }
    for(i=0;i<=8;i++)
    {
        if(strcmp(Matrix_Serial_Command[i],Serial_Data_point+4)==0)
        {
            
            switch (i)
            {
            case 0:
                Matrix_Structure->X_translation=Num;
				printf("Matrix_X_translation has been translate to %d\r\n",Matrix_Structure->X_translation);
                break;
            case 1:
                Matrix_Structure->Y_translation=Num;
				printf("Matrix_Y_translation has been translate to %d\r\n",Matrix_Structure->Y_translation);
                break;
            case 2:
                Matrix_Structure->Z_translation=Num;
				printf("Matrix_Z_translation has been translate to %d\r\n",Matrix_Structure->Z_translation);
                break;
            case 3:
                Matrix_Structure->X_rotation=Num;
				printf("Matrix_X_rotation has been translate to %d\r\n",Matrix_Structure->X_rotation);
                break;  
            case 4:
                Matrix_Structure->Y_rotation=Num;
				printf("Matrix_Y_rotation has been translate to %d\r\n",Matrix_Structure->Y_rotation);
                break;  
            case 5:
                Matrix_Structure->Z_rotation=Num;
				printf("Matrix_Z_rotation has been translate to %d\r\n",Matrix_Structure->Z_rotation);
                break;  
            case 6:
                Matrix_Structure->X_scale=Num;
				printf("Matrix_X_scale has been translate to %d\r\n",Matrix_Structure->X_scale);
                break;  
            case 7:
                Matrix_Structure->Y_scale=Num;
				printf("Matrix_Y_scale has been translate to %d\r\n",Matrix_Structure->Y_scale);
                break; 
            case 8:
                Matrix_Structure->Z_scale=Num;
				printf("Matrix_Z_scale has been translate to %d\r\n",Matrix_Structure->Z_scale);
                break;                                 
            default:
                break;
            }

        }

    }
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void USART1_IRQHandler(void)
{
	static uint8_t RxState = 0;
	static uint8_t pRxPacket = 0;
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART1);
		
		if (RxState == 0)
		{
			if (RxData == '@' && Serial_RxFlag == 0)
			{
				RxState = 1;
				pRxPacket = 0;
			}
		}
		else if (RxState == 1)
		{
			if (RxData == '$')
			{
				RxState = 0;
				Serial_RxPacket[pRxPacket] = '\0';
				Serial_RxFlag = 1;
			}
			else
			{
				Serial_RxPacket[pRxPacket] = RxData;
				pRxPacket ++;
			}
		}

		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
