#ifndef __LEDCUBE_H
#define __LEDCUBE_H

void Cube_Init(void);
void Cube_Print (unsigned char stair);
void Cube_Bright(void);
void Cube_Dark(void);
void Cube_Draw(uint8_t x,uint8_t y,uint8_t z);
void Cube_Wave(void);
void Cube_drawCube(uint8_t x, uint8_t y, uint8_t z, uint8_t s);
void Cube_DrawCube_Matrix(uint8_t x, uint8_t y, uint8_t z, uint8_t s,Matrix_Data *Matrix_Structure);


#endif
