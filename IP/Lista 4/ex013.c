#include <stdio.h>
#include <stdlib.h>

int dis[6][6];

void cidades () {

    dis[0][0] = 0;
    dis[1][1] = 0;
    dis[2][2] = 0;
    dis[3][3] = 0;
    dis[4][4] = 0;
    dis[5][5] = 0;

    dis[0][1] = 63;
    dis[0][2] = 210;
    dis[0][3] = 190;
    dis[0][4] = -1;
    dis[0][5] = 190;

    dis[1][0] = 63;
    dis[1][2] = 160;
    dis[1][3] = 150;
    dis[1][4] = 95;
    dis[1][5] = 10;

    dis[2][0] = 210;
    dis[2][1] = 160;
    dis[2][3] = 10;
    dis[2][4] = 1;
    dis[2][5] = 10;

    dis[3][0] = 190;
    dis[3][1] = 150;
    dis[3][2] = 10;
    dis[3][4] = 10;
    dis[3][5] = 20;

    dis[4][0] = 10;
    dis[4][1] = 95;
    dis[4][2] = 7;
    dis[4][3] = 21;
    dis[4][5] = 80;

    dis[5][0] = 190;
    dis[5][1] = 2;
    dis[5][2] = -1;
    dis[5][3] = 41;
    dis[5][4] = 80;
}

int calcdist(int * rota, int n) {
    int i;
    int dist;
    int inicio, fim;

    n--;

    for(i = 0, dist = 0; i < n; i++) {
        inicio = rota[i];
        fim = rota[i+1];
        if(dis[inicio][fim] == -1) return -1;
        
        dist += dis[inicio][fim];
    }

    return dist;
}

int main() {

    int n, dist;
    int *rota = NULL;
    int i = 0;

    cidades();

    scanf("%d", &n);

    rota = (int *)malloc(n * sizeof(int));

    for(i = 0; i < n; i++) {
        scanf("%d", &rota[i]);
    }

    dist = calcdist(rota, n);

    if(dist == -1) {
        printf("rota invalida!\n");
        return 0;
    }

    printf("%d\n", dist);

    free(rota);

    return 0;
}