#include <stdio.h>



long filtro(unsigned char v, short l, long b) 

{

  long r;

  unsigned short x = (unsigned short)v;

  unsigned short y = (unsigned short)l;



  if (x < y)

    r = 0;

  else

    r = (long)l;



  printf("v = %u, l = %d, b = %ld, r = %ld\n", (unsigned int)v, (int)l, b, r);



  return r;

}