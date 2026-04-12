#include <stdio.h>



int main() {

  int n = 64;
  printf("n = %d (0x%08X)\n", n, n);

  n = n >> 1;
  printf("n = %d (0x%08X)\n", n, n);

  printf("---\n");

  n = -24;
  printf("n = %d (0x%08X)\n", n, n);

  n = n >> 2;
  printf("n = %d (0x%08X)\n", n, n);

  return 0;

}