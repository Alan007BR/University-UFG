#include <stdio.h>

int main() {

    int n1, n2;
    int i = 0;

    scanf("%d %d", &n1, &n2);
    printf("\n");
    
    

    if ( n1 % 2 == 0 ) {

        printf("%d " , n1);
        

        while ( i < (n2 - 1)){
        i++;

            if ( i == (n2 - 1) ) {

                printf("%d\n" , n1 = n1 + 2);

                break;
            }

        printf("%d " , n1 = n1 + 2);

        }
    } else {
        printf("O PRIMEIRO NUMERO NAO E PAR");
    }

    return 0;
}