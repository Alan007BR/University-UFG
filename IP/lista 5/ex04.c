#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {

    double u;
    double x;
    double y;
    double z;
    double norma;

}  Dimen;


void calcnorm(int n, Dimen *dimen) {

    int i, j;
    int menor;
    Dimen temp;

        for(i = 0; i < n; i++) {
                dimen[i].norma = sqrt(dimen[i].u * dimen[i].u + dimen[i].x * dimen[i].x + dimen[i].y * dimen[i].y + dimen[i].z * dimen[i].z);
    }

    for(i = 0; i < n-1; i++) {
        menor = i;
                for(j = i; j < n; j++) {
                    if(dimen[j].norma < dimen[menor].norma) {
                        menor = j;
                    }
                }

                if(i != menor) {
                    temp = dimen[i];
                    dimen[i] = dimen[menor];
                    dimen[menor] = temp;
                }
                // t = x;
                // x = y;
                // y = t;                
    }


    for(i = 0; i < n; i++) {

    printf("Vetor: (%.2lf, %.2lf, %.2lf, %.2lf) Norma: %.2lf\n", dimen[i].u, dimen[i].x, dimen[i].y, dimen[i].z, dimen[i].norma);

    }

}


int main() {

    int n;
    int i = 0, j = 0;
    Dimen *dimen = NULL;

    scanf("%d", &n);

    dimen = calloc(n, sizeof(Dimen));

    for(i = 0; i < n; i++) {

        scanf("%lf%lf%lf%lf", &dimen[i].u, &dimen[i].x, &dimen[i].y, &dimen[i].z);

    }

    calcnorm(n, dimen);

    free(dimen);

    return 0;
}