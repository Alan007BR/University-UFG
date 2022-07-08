#include <stdio.h>

int intercalar(int *v1, int *v2, int q1, int q2, int *vr, int q3) {

    int i = 0;
    int final = q3, t;

    for (i = 0; i < q1; i++) {
        vr[i]= v1[i];
    }

    for (i = 0; i < q2; i++) {
        vr[i+q1]= v2[i];
    }

    while(final > 1) {
        for (i = 0; i < final - 1; i++) {
            if (vr[i] > vr[i+1]) {
                t = vr[i];
                vr[i] = vr[i+1];
                vr[i+1] = t;
            }
        }
            final--;
    }

    for (i = 0; i < q3; i++) {
        printf("%d\n", vr[i]);
    }

}

int main() {

    int q1, q2, q3;
    int i = 0;

    scanf("%d", &q1);
    scanf("%d", &q2);
    q3 = q1 + q2;
    int v1[q1], v2[q2], vr[q3];

    for (i = 0; i < q1; i++) {
        scanf("%d", &v1[i]);
    }

    for (i = 0; i < q2; i++) {
        scanf("%d", &v2[i]);
    }

    intercalar(v1, v2, q1, q2, vr, q3);

    return 0;
}