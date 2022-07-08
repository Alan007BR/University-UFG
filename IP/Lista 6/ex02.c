#include <stdio.h>

int main() {

    int i = 0;
    FILE *arq = NULL;

    arq = fopen("dados", "w");
    if(arq == NULL) return 0;

    for(i = 1; i <= 100; i++) {
    fprintf(arq, "%d\n", i);
    }

    fclose(arq);

    return 0;
}