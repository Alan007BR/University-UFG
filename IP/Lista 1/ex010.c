#include <stdio.h>

int main() {
    int numeros[3] = {0, 0, 0};
    char ordem[3];
    int aux = 0;

    int i = 0;
    int j = 0;

 
    scanf("%d %d %d\n", &numeros[0], &numeros[1], &numeros[2]);
    scanf("%c%c%c", &ordem[0], &ordem[1], &ordem[2]);


    for (i = 0; i < 2; i++) {
        for (j = i+1; j < 3; j++) {
            if (numeros[i] > numeros[j]) {
                aux = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = aux;
            }
        }
    }
    
 
    for (i = 0; i < 3; i++) {
        if (ordem[i] == 'A')
            printf("%d", numeros[0]);
        else if (ordem[i] == 'B')
            printf("%d", numeros[1]);
        else if (ordem[i] == 'C')
            printf("%d", numeros[2]);
        
        if (i != 2)
            printf(" ");
    }
    printf("\n");

    return 0;
}