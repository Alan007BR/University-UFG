#include <stdio.h>

int main() {
    //dados
    int tipo_ordem = 0;
    float numeros[3] = {0.0, 0.0, 0.0};
    float aux = 0;

    int i = 0;
    int j = 0;

    //leitura
    scanf("%d", &tipo_ordem);
    scanf("%f", &numeros[0]);
    scanf("%f", &numeros[1]);
    scanf("%f", &numeros[2]);

    //processamento (bubble sort)
    for (i = 0; i < 2; i++) {
        for (j = i+1; j < 3; j++) {
            if (numeros[i] > numeros[j]) {
                aux = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = aux;
            }
        }
    }
    
    //apresentacao dos resultados (saida)
    if (tipo_ordem == 1) {
        printf("%.2f %.2f %.2f\n", numeros[0], numeros[1], numeros[2]);
    } else if (tipo_ordem == 2) {
        printf("%.2f %.2f %.2f\n", numeros[2], numeros[1], numeros[0]);
    } else {
        printf("%.2f %.2f %.2f\n", numeros[1], numeros[2], numeros[0]);
    }

    return 0;
}