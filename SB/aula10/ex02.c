#include <stdio.h>



// Atualizar as macros para 'double'



// Definir a union para 'double'



double maxdouble(double a, double b)

{

  // TODO: seu código aqui...

}



int main()

{

   double a,b;



   a = 1.0;

   b = 2.0;

   printf("maior de %f %f = %f\n", a, b, maxdouble(a, b));



   a = -1.0;

   b = -2.0;

   printf("maior de %f %f = %f\n", a, b, maxdouble(a, b));



   a = 1.0;

   b = -2.0;

   printf("maior de %f %f = %f\n", a, b, maxdouble(a, b));



   a = 1.5;

   b = 1.75;

   printf("maior de %f %f = %f\n", a, b, maxdouble(a, b));



   a = -1.5;

   b = -1.75;

   printf("maior de %f %f = %f\n", a, b, maxdouble(a, b));



   a = -1.5;

   b = -2.5;

   printf("maior de %f %f = %f\n", a, b, maxdouble(a, b));



   a = 1.5;

   b = -1.75;

   printf("maior de %f %f = %f\n", a, b, maxdouble(a, b));

   return 0;

}