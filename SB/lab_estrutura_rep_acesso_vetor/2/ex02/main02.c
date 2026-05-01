#include <stdio.h>



extern unsigned char letters[];

extern int even;

extern int odd;



void ex02();



int main()

{

  ex02();



  printf("even = %d\n", even);

  printf("odd  = %d\n", odd);



  return 0;

}