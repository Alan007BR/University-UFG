#include <stdio.h>

int buscarn ( int *v, int n, int *vq, int qtbusc, int pos) {
    int i = 0, achou = 0;

    while (i < n && (!achou)) {
        if(v[i] == vq[pos]) {
            achou = 1;
            return 1;
        } else {i++;}
    }
    return 0;
}

int main() {
    int j = 0, i = 0, pos = 0, k = 0;
    int n, qtbusc, resul;
    scanf("%d", &n);
    int v[n];

    for(i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }

    scanf("%d", &qtbusc);
    int vq[qtbusc];

    for(j = 0; j < qtbusc; j++) {
        scanf("%d", &vq[j]);
    }

    for(pos = 0; pos < qtbusc; pos++) {
    resul = buscarn (v, n, vq, qtbusc, pos);
        if (resul == 1) {
            printf("ACHEI\n");
        } else {
            printf("NAO ACHEI\n");
        }
    }
    return 0;
}