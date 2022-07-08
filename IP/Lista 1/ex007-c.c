#include <stdio.h>

int main() {

    int dec, temp, i, j=1, bin = 0;
    scanf("%i", &dec);


    if ( dec > 255 || dec < 0)
    {
        printf("Numero invalido!");
            return 0;
    }

    else {

            temp = dec;

    while(temp != 0) {
        i = temp%2;
        bin = bin+(i*j);
        temp = temp/2;
        j=j*10;

    }

    printf("%8.8d", bin);
    }
    



    return 0;
}