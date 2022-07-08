#include <stdio.h>

int main() {

    int a = 0, b = 0, c = 0;
    float x1 = 0, x2 = 0;
    float delta = 0;

    scanf("%d %d %d", &a, &b, &c);
    // 0 = ax^2 + bx + c
    delta = b*b - 4 * a*c;
 //----------*/
    /* validar x1 x2 como +- 5
    if (x1 > 5 || x1 < -5 || x2 > 5 || x2 < -5) {

    } 
    */

    x1 = ( -b +sqrt(delta)) / (2*a);
    x2 = ( -b -sqrt(delta)) / (2*a);

    if( delta < 0){
        printf("POSICOES IMAGINARIAS\n");
    }

    if(delta >= 0){
        
        printf("POSICOES: X1=%.2f e X2=%.2f ", x1, x2);
        
        if(x1<-5 || x1>5 || x2<-5 || x2>5 ){
            printf("(FORA DO EXPERIMENTO)");
        }
        if((a+b+c) % 3==0){
        printf("\nFATO1: DESAPARECIDA"); 
        }
        if( c % 2==0 && c < a + b){
        printf("\nFATO2: ORIGEM");
        }
    }

    return 0;
}