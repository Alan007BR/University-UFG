#ifndef PROCESS_H
#define PROCESS_H

struct node_s {
  int  size;
  long values[5];
  int  used;
};

typedef struct node_s node_t;

void init(node_t *node);
void* new_sum();
void add_sum(void *handler, long val);
long get_sum(void *handler);

#endif