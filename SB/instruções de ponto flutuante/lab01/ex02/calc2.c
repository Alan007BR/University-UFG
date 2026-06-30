#include <stdio.h>
#include <math.h>

float calc2(float a, float b)
{
   double e = a + cos(b);
   printf("a = %f, b = %f, e = %f\n", (double)a, (double)b, e);
   return b;
}
