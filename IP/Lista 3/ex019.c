#include <stdio.h>


long int string2int( const char *string ) {
    int i = 0;
    long int num = 0;
    int d = 0;

        if(string[i] == '+') {
            d = 2;
            i++;
        }
        if(string[i] == '-') {
            d = 1;
            i++;
        }

    while ( string[i] != '\0' && string[i] >= '0' && string[i] <= '9') {


        num = num * 10 + string[i]-'0';
        i++;
    }
        if (d==1) {
            num = num*-1;
        } else if (d==2) {
            num = num;
        }
    return num;
}

int main() {
    int num;
    char string[32];

    while( scanf("%s", string) != EOF ) {

    num = string2int(string);

    printf("%d %d\n", num, num*2);

    }

    return 0;
}