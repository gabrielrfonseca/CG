#ifndef MYGL_H
#define MYGL_H

#include "core.h"
#include "frame_buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Declaração da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void);

//
// >>> Declare aqui as funções que você implementar <<<
//

typedef struct{ 
    unsigned char verm;   
    unsigned char verde;  
    unsigned char azul;   
    unsigned char alpha; 
} Cor; 

void PutPixel(int x, int y, Cor *);
void DrawLine(int, int, int, int, Cor *, Cor *);
void DrawTriangle(int, int, Cor *, int, int, Cor *, int, int, Cor *);
#endif  // MYGL_H
