    #include <stdio.h>
     
    somaDivisores(int n) {
     
        int soma = 0, i = 2;
     
        printf("%d = ", n);
        printf("1");
        for (i = 2; i <= n/2; i++) {
     
        if (n % i == 0) {
     
            printf(" + %d", i);
     
            soma = soma + i;
        }
     
        }
        soma++;
     
            printf(" = %d", soma);
     
        if (soma == n) {
            printf(" (NUMERO PERFEITO)\n");
        } else {
            printf(" (NUMERO NAO E PERFEITO)\n");
     
        }
     
        return 0;
    }
     
     
    int main() {
     
        int n;
     
        scanf("%d", &n);
     
        somaDivisores(n);    
     
        return 0;
    }