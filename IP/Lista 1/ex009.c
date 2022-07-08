#include <stdio.h>

int main() {

    int normal, invertido, aux;
    scanf("%i", &normal);

    if (normal >= 99999 || normal <= -99999) {
                printf("NUMERO INVALIDO");
    } else {

    invertido = 0;

    aux = normal;

    while (aux > 0) {
        invertido = (invertido*10) + (aux % 10);
        aux = aux / 10;
    }

    if (normal == invertido) {
        printf("PALINDROMO");
    } else {
        printf("NAO PALINDROMO");
    }
    }



    

    


    return 0;
}