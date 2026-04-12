#include <ctype.h>

#include <stdio.h>

int convertHexToInt(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    
    return -1;
}

int string2num(char *s, int base) {
    int a = 0;
    for ( ; *s; s++)
        a = a*base + convertHexToInt(*s);
    
    return a;
}


int main () {
    printf("==> %d\n", string2num("1234", 10) + 1);
    printf("==> %d\n", string2num("1234", 10) + 1);
    printf("==> %d\n", string2num("1234", 10) + string2num("1", 10));
    printf("==> %d\n", string2num("777", 8));
    printf("==> %d\n", string2num("777", 10));
    printf("%d\n", string2num("1a", 16));
    printf("%d\n", string2num("a09b", 16));
    printf("%d\n", string2num("k09b", 36));

  return 0;
}