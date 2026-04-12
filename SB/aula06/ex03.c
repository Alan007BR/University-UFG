#include <stdio.h>

int main() {

  signed char sc = -1;
  unsigned int ui = sc;

  printf("0x%08X\n", ui);

  return 0;
}