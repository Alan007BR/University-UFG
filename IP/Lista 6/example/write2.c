#include <stdio.h>

int main() {

    FILE *arq = NULL;
    int i = 0;
    int id1, id2;
    double m;

    arq = fopen("alfabeto", "wt");
    if(arq == NULL) return 0;

    scanf("%d %d", &id1, &id2);
    m = (id1 + id2)/2.0;

    fprintf(arq, "idade 1: %d");

    fclose(arq);

    return 0;
}