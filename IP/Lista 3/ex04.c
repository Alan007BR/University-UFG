#include <stdio.h>

int contleds (char * num, int leds) { // por dentro da mágica

    int j = 0;//variável para iteração

    for (j = 0; num[j]!='\0'; j++) { //pega o caracter número do vetor num[j] faz o for e depois incrementa
        leds = // leds recebe as comparações usando ternário
        num[j]== '0' ? leds=leds+6 ://operador ternário (condicao ? 'true':'false'), usei para ficar mais compacto do que switch ou else if
        num[j]== '1' ? leds=leds+2 :
        num[j]== '2' ? leds=leds+5 :
        num[j]== '3' ? leds=leds+5 :
        num[j]== '4' ? leds=leds+4 :
        num[j]== '5' ? leds=leds+5 :
        num[j]== '6' ? leds=leds+6 :
        num[j]== '7' ? leds=leds+3 :
        num[j]== '8' ? leds=leds+7 :
        leds+6;//numero 9, como é o fim das comparações, deixei fora para finalizar o ternário.
    }

    return leds;//retorna o resultado
}

int main() {

    int n, leds = 0;
    char num[128]; //char de caracter para armazenar os numeros

    int i = 0; //apenas variavéis de iteração
    scanf("%d", &n); //leitura do n de casos.

    for (i = 0; i < n; i++) { // contador para ler numeros de caso teste
        scanf("%s", num); //armazena o valor atual do numero

        leds = contleds(num, leds);//função que vai fazer a mágica;
        printf("%d leds\n", leds);
        leds=0;//resetar o valor dos leds para continuar a mágica;
    }

    return 0;
}