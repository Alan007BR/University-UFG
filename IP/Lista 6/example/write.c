#include <stdio.h>

int main() {

    FILE *arq = NULL;
    int i = 0;

    arq = fopen("alfabeto", "wt");
    if(arq == NULL) return 0;

    for(i = 'a'; i <= 'z'; i++) {
        fputc(i, arq);
        fputc(' ', arq);
    }
    fputc('\n', arq);
    for(i = 'A'; i <= 'Z'; i++) {
        fputc(i, arq);
        fputc(' ', arq);
    }
    fclose(arq);

    return 0;
}