#include "common.h"

int compare_guid(guid_t *id1, guid_t *id2)
{ 
  if (id1->part1 != id2->part1)
    return 0;
  if (id1->part2 != id2->part2)
    return 0;
  if (id1->part3 != id2->part3)
    return 0;
  for (int i = 0 ; i < 8 ; i++)
    if (id1->part4[i] != id2->part4[i])
      return 0;
  return 1;
}
