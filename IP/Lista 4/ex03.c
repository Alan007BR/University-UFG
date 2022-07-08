#include <stdio.h>
 
typedef struct {
 
    float n;
    float d;
} Fra;
 
void frac(Fra *fracoes, int t) {
 
    int i = 0, j = 0;
    int eq = 0;
 
    while(i < t) {
 
        for(j = i; j < t; j++) {
            if(fracoes[i].n / fracoes[i].d == fracoes[j].n / fracoes[j].d) {
                if (fracoes[i].n != fracoes[j].n || fracoes[i].d != fracoes[j].d) {
                eq++;
                printf("%.0f/%.0f equivalente a %.0f/%.0f\n", fracoes[i].n, fracoes[i].d, fracoes[j].n, fracoes[j].d);
                }
            }
        }
        i++;
    }
    if (eq == 0) {
        printf("Nao ha fracoes equivalentes na sequencia\n");
    }
 
}
 
 
int main() {
 
    int n, t = 0;
    int i = 0, j = 0;
    Fra fracoes[50];
 
    scanf("%d", &n);
 
    for(i = 0; i < n; i++) {
        scanf("%d", &t);
 
        printf("Caso de teste %d\n", i+1);
 
        for(j = 0; j < t; j++) {
            scanf("%f/%f", &fracoes[j].n, &fracoes[j].d);
        }
            frac(fracoes, t);
 
    }
 
 
    return 0;
}