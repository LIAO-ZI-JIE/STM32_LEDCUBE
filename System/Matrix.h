#ifndef _MATRIX_H
#define _MATRIX_H
/**
  * @brief  
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

void matrix_translate(float x,float y,float z,Matrix_Data *now);


#endif
