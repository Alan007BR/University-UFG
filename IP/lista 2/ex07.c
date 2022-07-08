#include <stdio.h>

void print_byte( unsigned char x) {
    int p = 128;

    while(p > 0) {
        if (x/p > 0) printf("1");
        else printf("0");
        x = x%p;
        p = p/2;
    }
}

void full_printf( unsigned char * pbyte, int t) {
    int i;
    for(i=0; i<t; i++) {
        print_byte( *pbyte);
        printf(" ");
        pbyte++;
    }
    printf("\n");
}

int main() {

    double n;
    unsigned char ch;
    unsigned short sh;
    unsigned int i;
    float f;

    scanf("%lf", &n);

    ch = sh = i = f = n;

    full_printf(&ch, sizeof(char));
    full_printf( (unsigned char * ) &sh, sizeof(short));
    full_printf( (unsigned char * ) &i, sizeof(int));
    full_printf( (unsigned char * ) &f, sizeof(float));
    full_printf( (unsigned char * ) &n, sizeof(double));

    return 0;
}