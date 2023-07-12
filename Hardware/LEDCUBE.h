#ifndef __LEDCUBE_H
#define __LEDCUBE_H

void Cube_Init(void);
void Cube_Print (unsigned char stair);
void Cube_Bright(void);
void Cube_Dark(void);
void Cube_Draw(int8_t x,int8_t y,int8_t z);
void Cube_Wave(void);
void Cube_drawCube(int8_t x, int8_t y, int8_t z, int8_t s);
void Cube_DrawCube_Matrix(int8_t x, int8_t y, int8_t z, int8_t s,Matrix_Data *Matrix_Structure);


#endif
