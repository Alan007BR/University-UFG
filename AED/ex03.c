#include <stdio.h>

int main() {

    int n, erro=0, flag = 0, primos = 0;
    int i = 3, j = 2, k = 2;

    scanf("%d", &n);

    if(n <= 0) { printf("erro\n"); return 0; }

    for(i = 0; i <= n; i++) {

        while(flag < n) {

            for(k = 2; k <= j/2; k++) {
                if(j % k == 0){
                    j++;
                    erro = 1;
                    break;
                }
            }

            if(j % j == 0 && erro == 0){
                primos += j;
                j++;
                flag++;
            }
        erro=0;

        }
    }

    printf("%d\n", primos);
    return 0;
}