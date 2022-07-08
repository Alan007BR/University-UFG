#include <stdio.h>

int main() {

    int m, num, cont;
    int sum = 0, start;

    scanf("%d", &m);


    for ( num = 1; num <= m; num++ ) {
        
        for ( start = 1; sum != num*num*num; start+= 2 ) {
                sum = 0;
                    for (cont = 0; cont < num; cont++) {
                        sum += + (start + 2*cont);
                    }
        }


    start += - 2;

    printf("%d*%d*%d = %d", num, num, num, start);
    for (cont = 1; cont < num; cont++) 
        printf("+%d", start + 2*cont);
        printf("\n"); 
    
   
    }

    

    return 0;
}