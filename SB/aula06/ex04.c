#include <stdio.h>

int main() {

  int n = 64;
  printf("n = %d (0x%08X)\n", n, n);

  n = n << 1;
  printf("n = %d (0x%08X)\n", n, n);

  printf("---\n");

  n = 12;
  printf("n = %d (0x%08X)\n", n, n);

  n = n << 4;
  printf("n = %d (0x%08X)\n", n, n);

  return 0;

}