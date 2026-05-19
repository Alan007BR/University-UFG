#include <stdio.h>



extern short v1[4];

extern int   v2[5];

extern char  v3[4];

extern long  v4[8];



extern int i;

extern short j;



void aux();



int main() {

   aux();



   printf("v3: ");

   for (i = 0; i < 4; i++) {

      printf("%d ", v3[i]);

   }



   printf("\nv4: ");

   for (i = 0; i < 8; i++) {

      printf("%ld ", v4[i]);

   }



   printf("\n");



   return 0;

}