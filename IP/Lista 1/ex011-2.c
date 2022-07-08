#include <stdio.h>

int main() {
    //dados
    float numeros[4] = {0.0, 0.0, 0.0, 0.0};
    float aux = 0;

    int i = 0;
    int j = 0;

    //leitura
    scanf("%f", &numeros[0]);
    scanf("%f", &numeros[1]);
    scanf("%f", &numeros[2]);
    scanf("%f", &numeros[3]);

    //processamento (bubble sort)
    for (i = 0; i < 3; i++) {
        for (j = i+1; j < 4; j++) {
            if (numeros[i] > numeros[j]) {
                aux = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = aux;
            }
        }
    }
    
    //apresentacao dos resultados (saida)
        printf("%.2f, %.2f, %.2f, %.2f\n", numeros[0], numeros[1], numeros[2], numeros[3]);

    return 0;
}