#include <stdio.h>


void liberar(int ** M, int n) {
    int i = 0;

    for (i = 0; i < n; i++) {
        free(M[i]);
    }

    free(M);
}

int **nova_matriz(int n) {

    int **M;
    int i = 0;

    M = (int **)malloc(n * sizeof(int**));

    for (i = 0; i < n; i++) {
        M[i] = (int *)malloc(n * sizeof(int));
    }

    return M;
}


int main() {

    int n;
    int i = 0, j = 0;
    int **M;

    scanf("%d", &n);

    M = nova_matriz(n);

    for (i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &M[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
            printf("%d\n", M[i][n-1-i]);
    }
    liberar(M, n);

    return 0;
}