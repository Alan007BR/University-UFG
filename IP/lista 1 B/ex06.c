#include <stdio.h>

int main() {

    int num, i = 1;
    int atual, ant, tc = 1, tr = 1;

    scanf("%d", &num);
    scanf("%d", &atual);

    for (i = 1; i < num; i++) {
        ant = atual;
        scanf("%d", &atual);

        if (atual > ant) {
            tc++;
            if(tc > tr) {
                tr = tc;
            }
        } else {
            tc = 1;
        }
    }

    printf("O comprimento do segmento crescente maximo e: %d\n", tr);


    return 0;
}