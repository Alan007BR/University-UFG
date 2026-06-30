#include <stdio.h>
#include "common.h"

rfid_object_t gObj;

int find(guid_t *id)
{
  int found = 0;
  rfid_object_t lObj[2];
  short pins[5];

  init_obj(&gObj, 0);
  init_obj(&lObj[0], 1);
  init_obj(&lObj[1], 2);

  init_pins(pins);

  if (compare_guid(&lObj[1].id, id))
    printf("Objeto local [1] igual!\n");

  if (compare_guid(id, &gObj.id))
    printf("Objeto global igual!\n");

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      if (pins[j] == lObj[i].pin) {
         found = 1;
         goto saida;
      }
    }
  }

saida:
  return found;
}
