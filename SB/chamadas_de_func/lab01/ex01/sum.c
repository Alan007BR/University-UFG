#include <stdio.h>



int sum(const char *prefix, int v1, short v2, int *s)

{

   *s = v1 + v2;

   printf("%s: %d\n", prefix, *s);

   return v1 * v2;

}



void show(long err, int val, int r)

{

   printf("err = %ld, val = %d, r = %d\n", err, val, r);

}