#include <stdio.h>

#include "aux.h"

struct Data data[] = {
  {1.0, 0},
  {4.1, 0},
  {5.8, 0},
  {7.3, 0}
};

void t_init(struct Temperatura *t) {
  t->scale = 'C';
  t->value = 10.0;
  t->repeated = 1;
}

float collect(struct Data *ptr, float limit, int count);

int main()
{
  float f = collect(data, 5.0, 4);
  printf("Main = %f\n", f);
  return 0;
}