#include <stdio.h>

int fibonacci(int t1, int t2, int n) {

    int term;

    int atual;

    for(term = 3; term <= n; term++) {
    atual = t1;
    atual = t2 + t1;
    t1 = t2;
    t2 = atual;
    // t4 = t3 + t2;
    //t5 = t4 + t3;
    }
    printf("%d\n", atual);

}


int main() {

    int t1, t2, n;

    scanf("%d %d %d", &t1, &t2, &n);

    fibonacci(t1, t2, n);

    return 0;
}