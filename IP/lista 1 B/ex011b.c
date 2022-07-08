#include <stdio.h>


    int inv(int t) {
        
        int c, d, u;
        c = t/100;
        d = t%100/10;
    	u = t%10;

        return u*100 + d*10 + c;
    }

int main () {

    int t, a, b;

    scanf("%d", &t);
    
    while (t > 0) {
    
    scanf("%d %d", &a, &b);
    
    a = inv(a);
    b = inv(b);
        
    if( a < b ) {
            printf("%d\n", b);
        } else {
            printf("%d\n", a);
        }
            t--;
    }



    return 0;
}