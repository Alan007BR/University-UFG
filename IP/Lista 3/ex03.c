#include <stdio.h>

void invert(int * v, int n) {

    int temp = n;

    while (temp > 0) {
        temp--;
        printf("%d ", v[temp]);
    }

}

int main() {

    int n;
    int i = 0;

    scanf("%d", &n);

    int v[n];

    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    invert(v, n);

    return 0;
}