#include <stdio.h>


unsigned long int fat( unsigned int n) {

    unsigned long int i;
    unsigned long int r = 1;

    if (n == 0) {
        printf("0! = 1");
        return 0;
    }

    for (i = n; i > 1; i--) {        
    
    r = r * i;
    
    }

    printf("%lu! = %lu\n", n, r);

}


int main() {

    int n;

    scanf("%lu", &n);

    fat(n);


    return 0;
}