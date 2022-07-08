#include <stdio.h>

int main() {

    int i = 0;
    int v[100];
    FILE *arq = NULL;

    arq = fopen("dados", "wb");
    if(arq == NULL) return 0;

    for (i = 1; i <= 100; i++) {
        v[i] = i;
    }

    fwrite(v, sizeof(int), 101, arq);

    fclose(arq);

    return 0;
}