#include "stm32f10x.h"                  // Device header
#include "LEDCUBE.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define pi 3.1415926
/**
  * @brief  矩陣結構體
  */
typedef struct 
{
    int X_rotation;
    int Y_rotation;
    int Z_rotation;
    int X_translation;
    int Y_translation;
    int Z_translation;
    int X_scale;
    int Y_scale;
    int Z_scale;
} Matrix_Data;
/**
  * @brief   製作平移矩陣
  * @param   矩陣資料結構體
  * @retval  指向申請空間的地址
  */
float** Make_Matrix_translation(Matrix_Data* Matrix_structer)
{
	int i;
    float x,y,z;
	x=Matrix_structer->X_translation;
    y=Matrix_structer->Y_translation;
    z=Matrix_structer->Z_translation;
    float** arr = (float**)malloc(sizeof(float*) * 4);
	if (arr != NULL)
	{
		for (i = 0; i < 4; i++)
		{
			arr[i] = (float*)malloc(sizeof(float) * 4);
		}
	}
    arr[0][0]=1;
    arr[0][1]=0;
    arr[0][2]=0;
    arr[0][3]=x;
    arr[1][0]=0;
    arr[1][1]=1;
    arr[1][2]=0;
    arr[1][3]=y;
    arr[2][0]=0;
    arr[2][1]=0;
    arr[2][2]=1;
    arr[2][3]=z;
    arr[3][0]=0;
    arr[3][1]=0;
    arr[3][2]=0;
    arr[3][3]=1;
	return arr;
}
/**
  * @brief  製作沿X軸旋轉矩陣
  * @param   矩陣資料結構體
  * @retval  指向申請空間的地址
  */
float** Make_Matrix_X_Rotation(Matrix_Data* Matrix_structer)
{

	int i;
    float x;
    float** arr = (float**)malloc(sizeof(float*) * 4);
	if (arr != NULL)
	{
		for (i = 0; i < 4; i++)
		{
			arr[i] = (float*)malloc(sizeof(float) * 4);
		}
	}
	x=(Matrix_structer->X_rotation)*(pi/180);
    arr[0][0]=1;
    arr[0][1]=0;
    arr[0][2]=0;
    arr[0][3]=0;
    arr[1][0]=0;
    arr[1][1]=cos(x);
    arr[1][2]=-sin(x);
    arr[1][3]=0;
    arr[2][0]=0;
    arr[2][1]=sin(x);
    arr[2][2]=cos(x);
    arr[2][3]=0;
    arr[3][0]=0;
    arr[3][1]=0;
    arr[3][2]=0;
    arr[3][3]=1;
	return arr;
}
/**
  * @brief  製作沿Y軸旋轉矩陣
  * @param   矩陣資料結構體
  * @retval  指向申請空間的地址
  */
float** Make_Matrix_Y_Rotation(Matrix_Data* Matrix_structer)
{

	int i;
    float y;
    float** arr = (float**)malloc(sizeof(float*) * 4);
	if (arr != NULL)
	{
		for (i = 0; i < 4; i++)
		{
			arr[i] = (float*)malloc(sizeof(float) * 4);
		}
	}
	y=(Matrix_structer->Y_rotation)*(pi/180);
    arr[0][0]=cos(y);
    arr[0][1]=0;
    arr[0][2]=sin(y);
    arr[0][3]=0;
    arr[1][0]=0;
    arr[1][1]=1;
    arr[1][2]=0;
    arr[1][3]=0;
    arr[2][0]=-sin(y);
    arr[2][1]=0;
    arr[2][2]=cos(y);
    arr[2][3]=0;
    arr[3][0]=0;
    arr[3][1]=0;
    arr[3][2]=0;
    arr[3][3]=1;
	return arr;
}
/**
  * @brief  製作沿Z軸旋轉矩陣
  * @param   矩陣資料結構體
  * @retval  指向申請空間的地址
  */
float** Make_Matrix_Z_Rotation(Matrix_Data* Matrix_structer)
{

	int i;
    float z;
    float** arr = (float**)malloc(sizeof(float*) * 4);
	if (arr != NULL)
	{
		for (i = 0; i < 4; i++)
		{
			arr[i] = (float*)malloc(sizeof(float) * 4);
		}
	}
    z=(Matrix_structer->Z_rotation)*(pi/180);
    arr[0][0]=cos(z);
    arr[0][1]=-sin(z);
    arr[0][2]=0;
    arr[0][3]=0;
    arr[1][0]=sin(z);
    arr[1][1]=cos(z);
    arr[1][2]=0;
    arr[1][3]=0;
    arr[2][0]=0;
    arr[2][1]=0;
    arr[2][2]=1;
    arr[2][3]=0;
    arr[3][0]=0;
    arr[3][1]=0;
    arr[3][2]=0;
    arr[3][3]=1;
	return arr;
}
/**
  * @brief  製作放大矩陣
  * @param   矩陣資料結構體
  * @retval  指向申請空間的地址
  */
float** Make_Matrix_scale(Matrix_Data* Matrix_structer)
{

	int i,x,y,z;
	x=Matrix_structer->X_scale;
    y=Matrix_structer->Y_scale;
    z=Matrix_structer->Z_scale;
    float** arr = (float**)malloc(sizeof(float*) * 4);
	if (arr != NULL)
	{
		for (i = 0; i < 4; i++)
		{
			arr[i] = (float*)malloc(sizeof(float) * 4);
		}
	}
    arr[0][0]=x;
    arr[0][1]=0;
    arr[0][2]=0;
    arr[0][3]=0;
    arr[1][0]=0;
    arr[1][1]=y;
    arr[1][2]=0;
    arr[1][3]=0;
    arr[2][0]=0;
    arr[2][1]=0;
    arr[2][2]=z;
    arr[2][3]=0;
    arr[3][0]=0;
    arr[3][1]=0;
    arr[3][2]=0;
    arr[3][3]=1;
	return arr;
}
/**
  * @brief  製作全為0的矩陣
  * @param   矩陣資料結構體
  * @retval  指向申請空間的地址
  */
float** Make_Matrix_Init(void)
{
	int i,j;
    float** arr = (float**)malloc(sizeof(float*) * 4);
	if (arr != NULL)
	{
		for (i = 0; i < 4; i++)
		{
			arr[i] = (float*)malloc(sizeof(float) * 4);
		}
	}
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            arr[i][j]=0;
        }
    }
	return arr;
}
/**
  * @brief  釋放矩陣
  * @param   指向申請空間的地址
  * @retval  無
  */
void free_Matrix(float** src)
{
    int i;
    for(i = 0;i < 4; i++)
    {
        free(src[i]);
    }
    free(src);
}
/**
  * @brief  將矩陣相乘
  * @param  要相乘的左矩陣的地址
  * @param  要相乘的右矩陣的地址
  * @param  輸出結果的矩陣的地址
  * @retval 無
  */
void Matrix_Multiply(float ** Matrix_left,float ** Matrix_right,float ** Matrix_result)
{
    int i,j,k;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
            Matrix_result[i][j]=0.0;
			for (k = 0; k < 4; k++)
			{
				Matrix_result[i][j] += Matrix_left[i][k] * Matrix_right[k][j];
			}
		}
    }
}
/**
  * @brief  複製矩陣將一矩陣複製到二矩陣
  * @param  要複製的一矩陣地址
  * @param  要被複製的二矩陣地址
  * @retval 無
  */
void Matrix_copy(float **Matrix_one,float **Matrix_two)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            Matrix_two[i][j]=Matrix_one[i][j];
        }
    }
}
/**
  * @brief  輸出依結構體資料創建的矩陣
  * @param  數據資料結構體
  * @retval 指向創建矩陣的地址
  */
float** Make_New_Matrix(Matrix_Data *now)
{
    float** Matrix_New=Make_Matrix_Init();
    float** Matrix_temp=Make_Matrix_Init();
    float** Matrix_traslate=Make_Matrix_translation(now);
    float** Matirx_X_Rotation=Make_Matrix_X_Rotation(now);
    float** Matrix_Y_Rotation=Make_Matrix_Y_Rotation(now);
    float** Matrix_Z_Rotation=Make_Matrix_Z_Rotation(now);
    float** Matrix_scale=Make_Matrix_scale(now);  
    Matrix_Multiply(Matirx_X_Rotation,Matrix_Y_Rotation,Matrix_New);
    Matrix_copy(Matrix_New,Matrix_temp);
    Matrix_Multiply(Matrix_Z_Rotation,Matrix_temp,Matrix_New);
    Matrix_copy(Matrix_New,Matrix_temp);
    Matrix_Multiply(Matrix_scale,Matrix_temp,Matrix_New);
    Matrix_copy(Matrix_New,Matrix_temp);
    Matrix_Multiply(Matrix_traslate,Matrix_temp,Matrix_New);  
    free_Matrix(Matrix_temp);
    free_Matrix(Matrix_traslate);
    free_Matrix(Matirx_X_Rotation);
    free_Matrix(Matrix_Y_Rotation);
    free_Matrix(Matrix_Z_Rotation);
    free_Matrix(Matrix_scale);
    return Matrix_New; 
}
/**
  * @brief  將數據依矩陣變換
  * @param  要變換的X座標
  * @param  要變換的Y座標
  * @param  要變換的Z座標
  * @param  變換矩陣數據的結構體地址
  * @retval 無
  */
void matrix_translate(float x,float y,float z,Matrix_Data *now)
{   
    int i,j;
    float out_x,out_y,out_z;
    float** New_Matrix;
    static Matrix_Data last={
        .X_rotation=0,
        .X_scale=0,
        .X_translation=0,
        .Y_rotation=0,
        .Y_scale=0,
        .Y_translation=0,
        .Z_rotation=0,
        .Z_scale=0,
        .Z_translation=0
    };
    static float translate[4][4]={{1,0,0,0},
                                  {0,1,0,0},
                                  {0,0,1,0},
                                  {0,0,0,1}
                                  };

    if (memcmp(&last,now,sizeof(last)))
    {   
        New_Matrix=Make_New_Matrix(now);
        for(j=0;j<4;j++)
        {
            for(i=0;i<4;i++)
            {
                translate[j][i]=New_Matrix[j][i];
            }
        }
        free_Matrix(New_Matrix);
		memcpy(&last,now,sizeof(last));
    }
    out_x=x*translate[0][0]+y*translate[0][1]+z*translate[0][2]+translate[0][3];
    out_y=x*translate[1][0]+y*translate[1][1]+z*translate[1][2]+translate[1][3];
    out_z=x*translate[2][0]+y*translate[2][1]+z*translate[2][2]+translate[2][3];
	Cube_Draw(out_x,out_y,out_z);
}
