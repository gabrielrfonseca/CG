#include "mygl.h"
#define DIR(x) ((x)>=0?(x):-(x)) //apenas para mudar direcao em relacao a x e y 

//
// >>> Defina aqui as funções que você implementar <<< 
//

void PutPixel(int x, int y, Cor *cor){
    const unsigned int startPoint = x * 4 + y * IMAGE_WIDTH * 4;
    fb_ptr[startPoint] = cor->verm;
    fb_ptr[startPoint + 1] = cor->verd;
    fb_ptr[startPoint + 2] = cor->azl;
    fb_ptr[startPoint + 3] = cor->alpha;
}

void DrawLine(int x0, int y0, int x1, int y1, Cor *cor1, Cor *cor2){
    // Se a reta tiver sido desenhada nos quadrantes do lado negativo da reta X, troca os pontos para jogar no lado positivo do X
    bool mudaCor = false;
    if (x1 < x0){
        swap(&x0, &x1);
        swap(&y0, &y1);
        mudaCor = true;
    }

    // Calcula DeltaY e DeltaX
    int dx = x1 - x0;
    int dy = y1 - y0;

    // Inicia variável para contar iterações para interpolação e calcula distância dos pontos
    float passoIteracao = 0.0;
    float dist = sqrt((dx*dx)+(dy*dy));

    // Inicia variáveis de referência para interpolação
    Cor corRef;

    // Se mudaCor for true, significa que os pontos foram trocados, então começa interpolando pela segunda cor
    if (mudaCor){
        corRef.verm = cor2->verm;
        corRef.verd = cor2->verd;
        corRef.azl = cor2->azl;
    }else{ // Se não, interpola cada um com sua cor normal
        corRef.verm = cor1->verm;
        corRef.verd = cor1->verd;
        corRef.azl = cor1->azl;
    }
    
    corRef.alpha = 255; // Alpha sempre em 255 para ter a maior visibilidade

    if (dx == 0){       // Para desenhar linhas retas basta apenas um for
        bool inverte = false;
        if (dy < 0){
            swap(&y0, &y1);
            inverte = true;
        }
            
        
        for (int i = y0; i < y1; i++){
            passoIteracao += 1/dist;
            if (!mudaCor && !inverte)
                ApplyInterpolation(&corRef, *cor1, *cor2, passoIteracao);
            else
                ApplyInterpolation(&corRef, *cor2, *cor1, passoIteracao);
            PutPixel(x0, i, &corRef);
        }
    }else if (dy == 0){ // Para desenhar linhas retas basta apenas um for
        if (dx < 0)
            swap(&x0, &x1);
        
        for (int i = x0; i < x1; i++){
            passoIteracao += 1/dist;
            if (!mudaCor)
                ApplyInterpolation(&corRef, *cor1, *cor2, passoIteracao);
            else
                ApplyInterpolation(&corRef, *cor2, *cor1, passoIteracao);
            PutPixel(i, y0, &corRef);
        }
    }else{

        if (DIR(dy) > DIR(dx)){ // Faz todo o desenho em relação a Y em vez de X
            bool inverter = false;
            passoIteracao += 1/dist;

            if (dy < 0){
                dy *= -1;

                inverter = true;
            }
            
            int d = 2 * dx - dy; // d inicial
            int incrE = 2 * dx;
            int incrNE = 2 * (dx - dy);

            int x = x0;
            int y = y0;
            
            PutPixel(x, y, &corRef);

            if (inverter){ // Se o y for negativo e o desenho vai ser em relação a ele, loop compara até y ser igual a y1, seu ponto final
                while (y > y1){
                    if (d <= 0){
                        d += incrE;
                        if (inverter)
                            y--;
                        else
                            y++;
                    }
                    else{
                        d += incrNE;
                        if (inverter)
                            y--;
                        else
                            y++;
                        x++;
                    }
                    passoIteracao += 1/dist;
                    if (!mudaCor)
                        ApplyInterpolation(&corRef, *cor1, *cor2, passoIteracao);
                    else
                        ApplyInterpolation(&corRef, *cor2, *cor1, passoIteracao);
                    PutPixel(x, y, &corRef);
                }
            }else{                  // Nesse caso o desenho é em relação a Y, mas ele não é negativo, então segue a mesma lógica do X com tudo trocado por Y
                while (y <= y1){
                    if (d <= 0){
                        d += incrE;
                        if (inverter)
                            y--;
                        else
                            y++;
                    }
                    else{
                        d += incrNE;
                        if (inverter)
                            y--;
                        else
                            y++;
                        x++;
                    }
                    passoIteracao += 1/dist;
                    if (!mudaCor)
                        ApplyInterpolation(&corRef, *cor1, *cor2, passoIteracao);
                    else
                        ApplyInterpolation(&corRef, *cor2, *cor1, passoIteracao);
                    PutPixel(x, y, &corRef);
                }
            }

        }
        else{ // Faz tudo em relação a X, do jeito normal!
            bool inverter = false;
            passoIteracao = 1/dist;

            if (dy < 0){
                dy *= -1;
                inverter = true;
            }

            int d = 2 * dy - dx; // d inicial
            int incrE = 2 * dy;
            int incrNE = 2 * (dy - dx);

            int x = x0;
            int y = y0;

            PutPixel(x, y, &corRef);

            while (x <= x1){
                if (d <= 0){
                    d += incrE;
                    x++;
                }
                else{
                    d += incrNE;
                    x++;
                    if (inverter)
                        y--;
                    else
                        y++;
                }
                passoIteracao += 1/dist;
                if (!mudaCor)
                    ApplyInterpolation(&corRef, *cor1, *cor2, passoIteracao);
                else
                    ApplyInterpolation(&corRef, *cor2, *cor1, passoIteracao);
                PutPixel(x, y, &corRef);
            }
        }
    }
}

void DrawTriangle(int x1, int y1, Cor *cor1, int x2, int y2, Cor *cor2, int x3, int y3, Cor *cor3){
    DrawLine(x1, y1, x2, y2, cor1, cor2);
    DrawLine(x2, y2, x3, y3, cor2, cor3);
    DrawLine(x3, y3, x1, y1, cor3, cor1);
}



void swap(int *x, int *y){
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


void ApplyInterpolation(Cor *corAtual, Cor cor1, Cor cor2, float distancia){
    corAtual->verm = (cor2.verm*distancia) + ((1-distancia)*cor1.verm);
    corAtual->verd = (cor2.verd*distancia) + ((1-distancia)*cor1.verd);
    corAtual->azl = (cor2.azl*distancia) + ((1-distancia)*cor1.azl);
}


Cor branco = {.verm = 255, .verd = 255, .azl = 255, .alpha = 255};
Cor vermelho = {.verm = 255, .verd = 0, .azl = 0, .alpha = 255};
Cor verde = {.verm = 0, .verd = 255, .azl = 0, .alpha = 255};
Cor azul = {.verm = 0, .verd = 0, .azl = 255, .alpha = 255};
Cor CorRandom = {.verm = 100, .verd = 59, .azl = 156, .alpha = 255};


// Definição da função que chamará as funções implementadas pelo aluno
void MyGlDraw(void) {

    //
    // >>> Chame aqui as funções que você implementou <<<
    //
    // PutPixel(0, 0, &verde);
    // PutPixel(2, 0, &azul);
    // PutPixel(4, 0, &vermelho);
    // PutPixel(6, 0, &branco);
    // PutPixel(8, 0, &CorRandom);
 
    // DrawLine(0, 0, 511, 511, &branco, &vermelho);
    // DrawLine(511, 0, 0, 511, &branco, &verde);
    
    // DrawLine(256, 127, 256, 383, &branco, &azul);
    // DrawLine(127, 256, 383, 256, &branco, &CorRandom);
    
    // DrawLine(383, 0, 127, 511, &branco, &vermelho);
    // DrawLine(127, 0, 383, 511, &branco, &azul);
    DrawTriangle(0, 255, &vermelho, 127, 255, &verde, 127, 0, &azul);

}
