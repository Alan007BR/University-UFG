#include <stdio.h>

char tamanho(char *aux) {
    int i = 0;
    int letras = 0;

    for (i = 0; aux[i] != '\0'; i++) {
        if(aux[i] != ' ') {
            letras++;
        }
    }
    return letras;
}

int main() {

    int n, c, f;
    int i = 0, j = 0;
    char aux[10];

    scanf("%d", &n);
    
    while (n--) {

    scanf("%d %d", &c, &f);

    for (i = c; i <= f; i++) {
        printf("%d", i);
    }
    for (i = f; i >= c; i--) {
        sprintf(aux,"%d", i);
        for(j = tamanho(aux)-1; j >= 0; j--) {
            printf("%c", aux[j]);
        }
    }
    printf("\n");   
    }

    return 0;
}