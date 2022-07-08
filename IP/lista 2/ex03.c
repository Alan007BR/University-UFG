    #include <stdio.h>
     
     
    int separaDigitos(int n) {
     
        int c, d, u;
        c = n/100;
        d = n%100/10;
        u = n%10;
     
        
        printf("%d\n", u*100 + d*10 + c);
    }
     
     
    int main() {
     
        int n;
     
        scanf("%d", &n);
     
        separaDigitos(n);
     
     
        return 0;
    }