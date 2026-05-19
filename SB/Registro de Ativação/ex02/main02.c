#include <stdio.h>

long aux(int i, long *ptr);
long v = 10;


int main() {

  int y = 15;
  long r = aux(y, &v);

  printf("main: v = %ld, y = %d, r = %ld\n", v, y, r);
  return 0;
}