/* +
Dois automóveis partem de duas cidades A e B ligadas por uma rodovia. O primeiro
automóvel parte da cidade A em velocidade constante com destino a cidade B e o segundo parte
da cidade B em velocidade constante com destino a cidade A. Considere que os dois automóveis
partem simultaneamente. Elabore um programa usando a linguagem C para receber a distância
que separa as cidades, a velocidade do primeiro automóvel e a velocidade do segundo
automóvel e determinar o momento e o local em que os automóveis se encontram. Considere
que a distância entre as cidades deve ser informada em quilômetros (Km) e as velocidades dos
automóveis em quilômetros por hora (Km/h). Considere também que a referência para o ponto
de encontro dos automóveis deve ser a distância com relação à cidade A
*/

#include <stdio.h>

int main() {

    double distance, point;
    int vel1, vel2;
    double t = 0;

    scanf("%lf", &distance);

    if(distance <= 0) {
        printf("erro\n"); return 0;
    }

    scanf("%d", &vel1);
        if(vel1 <= 0) {
        printf("erro\n"); return 0;
        }

    scanf("%d", &vel2);
        if(vel2 <= 0) {
        printf("erro\n"); return 0;
    }
    
    t = distance / (vel1 + vel2);
    point = vel1 * t;

    printf("%.2lf\n", t);
    printf("%.1lf\n", point);
   

    return 0;
}