#include <stdio.h>


int main() {

    double somatic;
    int n;
    int i = 0;

    const K = 1;

    scanf("%d", &n);

    if (n < 1) {
    printf("Numero invalido!");

        return 0;
    }

    //somatic 1/i = 1 + 1/2 + 1/3 + 1/4 + 1/5 + 1/6 + 1/7 + 1/8 + 1/9 + 1/10 ..... + 1/k

    while ( i < n ) {

        i++;
        somatic = somatic + (K/(double)i);

    }

    printf("%lf", somatic);

    return 0;
}

