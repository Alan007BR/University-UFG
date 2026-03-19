#include <stdio.h>



int main (void) {

  int x = 0xffffffff;
  unsigned int y = 2;

  printf("x = %d, y = %u\n", x, y);
  printf("x é menor do que y? %s\n", (x < y) ? "sim" : "não");

  return 0;

}