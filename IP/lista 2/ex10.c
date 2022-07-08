#include <stdio.h>
 
double compute_pi(int n) {
                 
    int n1 = 2, n2 = 1;
    double total = 1;
    int i = 1;
 
        for(i=1; i<=n; i++) {
        total *= n1/(double)n2;
            if(i%2 == 0) n1+=2;
            else n2+=2;
    }
    return total * 2;
}
 
int main() {
 
    double result;
    int n;
    scanf("%d", &n);
 
    result = compute_pi(n);
 
    printf("%.12lf\n", result);
 
    return 0;
}