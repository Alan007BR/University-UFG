#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    double x;
    double y;
    double z;
    double u;

} Pontos;

double calcdist(Pontos p1, Pontos p2) {
    double x, y, z, u;

    x = p1.x - p2.x;
    x *= x;

    y = p1.y - p2.y;
    y *= y;

    z = p1.z - p2.z;
    z *= z;

    u = p1.u - p2.u;
    u *= u;

    return sqrt(u + x + y + z);
}


int main() {

    Pontos *pontos = NULL;
    int n;
    int i = 0;

    scanf("%d", &n);

    pontos = calloc(n, sizeof(Pontos));

    for (i = 0; i < n; i++) {
        scanf("%lf %lf %lf %lf", &pontos[i].u, &pontos[i].x, &pontos[i].y, &pontos[i].z);
    }

    for (i = 0; i < n-1; i++) {
        printf("%.2lf\n", calcdist(pontos[i], pontos[i+1]));
    }

    free(pontos);

    return 0;
}