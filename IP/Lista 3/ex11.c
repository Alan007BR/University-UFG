#include <stdio.h>
 
int mediana(long int *num, long int n) {
    double med;
    long int i = 0;
    double p = 0.0;
    long int indice = 0;
    if (n % 2 != 0) {//se o num for impar
        i = (n/2);
        med = num[i];
    printf("%.2lf\n", med);
    } else {//se o num for par
        i = n/2;
        p = (num[i] + num[i-1]);
        printf("%.2lf\n", p/2);
    } 
    return med;
}
void ordenar(long int *num, long int n) {
    long int final = n;
    long int t;
    long int i = 0;
 
    while (final > 1) {//bom e velho bobble sort
        for (i = 0; i < final - 1; i++) {
            if (num[i] > num[i + 1]) {
                t = num[i];
                num[i] = num[i + 1];
                num[i + 1] = t;
            }
        }
        final--;
    }
}
int main() {
    long int n;
    int i = 0;
    double resul;
    //entrada
    scanf("%ld", &n);
    if (n == 0) {
        return 0;
    }
    long int num[n];
    for (i = 0; i < n; i++) {
        scanf("%ld", &num[i]);
    }
    ordenar(num, n);
    resul = mediana(num, n);
 
    return 0;
}