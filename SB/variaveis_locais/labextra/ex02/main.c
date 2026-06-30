#include <stdio.h>
#include "process.h"

long sum(node_t *nodes, int size){

  int i, j;
  void *h = new_sum();

  for (i = 0; i < size; i++) {
    for (j = 0; j < nodes[i].used; j++)
      add_sum(h, nodes[i].values[j]);
  }

  return get_sum(h);
}



int main(){
  node_t nodes[2];
  init(nodes);
  printf("sum = %ld\n", sum(nodes, 2));

  return 0;
}