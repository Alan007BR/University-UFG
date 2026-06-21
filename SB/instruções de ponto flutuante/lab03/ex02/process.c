#include <stdio.h>

double factor = 15.0;
float vets[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

int main()
{
   int i;
   int j = 0;
   long drop = 50;
   double copy[5];

   for (i = 0; i < 5; i++) {
      double tmp = vets[i] * factor;
      if (tmp < drop)
        copy[j++] = tmp;
   }

   for (i = 0; i < j; i++)
      printf("copy[%d] = %f\n", i, copy[i]);

   return 0;
}