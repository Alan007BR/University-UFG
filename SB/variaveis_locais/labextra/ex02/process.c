#include <stdlib.h>

#include <string.h>



#include "process.h"



void* new_sum() {

  long *ptr = (long*)malloc(sizeof(long));

  *ptr = 0;

  return ptr;

}



void add_sum(void *handler, long val) {

  long *ptr = (long*)handler;

  *ptr = *ptr + val;

  handler = NULL;

}



long get_sum(void *handler) {

  long s = *((long*)handler);

  free(handler);

  handler = NULL;

  return s;

}



void init(node_t *node)

{

  node_t tmp[2] = {

    {5, {1,2,3,1,1}, 3},

    {5, {4,5,6,7,1}, 4}

  };



  memcpy(node, tmp, 2 * sizeof(node_t));

}