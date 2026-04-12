#include <stdio.h>

int leading_zeros(unsigned short n) {
    
}

int main() {
    printf("leading_zeros(0): %d zeros\n", leading_zeros(0)); // 16 zeros
    printf("leading_zeros(0x0083): %d zeros\n", leading_zeros(0x0083)); // 8 zeros
    printf("leading_zeros(0x0607): %d zeros\n", leading_zeros(0x0607)); // 4 zeros
    printf("leading_zeros(24432): %d zeros\n", leading_zeros(24432)); // 1 zero
    printf("leading_zeros(0xC2A4): %d zeros\n", leading_zeros(0xC2A4)); // 0 zeros
    
    return 0;
}