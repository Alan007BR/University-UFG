#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

guid_t g1 = { 0x752f3136, 0x4e16, 0x4fdc, { 0xa2, 0x2a, 0xe5, 0xf4, 0x68, 0x12, 0xf4, 0xca } };
guid_t g2 = { 0xbc62157e, 0x3e33, 0x4fec, { 0x99, 0x20, 0x2d, 0x3b, 0x36, 0xd7, 0x50, 0xdf } };
guid_t g3 = { 0x837bc839, 0x8fe3, 0x388b, { 0xa4, 0x30, 0x5f, 0x2c, 0x84, 0x98, 0x23, 0xd7 } };

void init_obj(rfid_object_t *obj, int base)
{
  guid_t *id;
  switch (base) {
  case 0:  id = &g1; break;
  case 1:  id = &g2; break;
  default: id = &g3; break;
  }

  memcpy(&obj->id, id, sizeof(guid_t));
  obj->pin = base % 3;
  obj->enabled = 1;
}


void init_pins(short pins[5])
{
  for (int i = 0; i < 5; i++)
    pins[i] = i % 3;
}

int main()
{
  if (find(&g1))
    printf("Pin encontrado\n");
  else
    printf("Pin não encontrado\n");
}
