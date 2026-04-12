#include <stdio.h>

unsigned char rotate_left(unsigned char x, int n){
    int value_shifted = 0;

    for(int i = 0; i < 4; i++) {
        value_shifted = (x << n) | (x >> (8 - n));   
    }
    return value_shifted;
}

int main() {
    printf("rotate_left(0x61, 1): 0x%02x\n", rotate_left(0x61, 1)); // (1100 0010)
    printf("rotate_left(0x61, 2): 0x%02x\n", rotate_left(0x61, 2)); // (1100 0010)
    printf("rotate_left(0x61, 3): 0x%02x\n", rotate_left(0x61, 7)); // (1100 0010)
    return 0;
}