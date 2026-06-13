#ifndef COMMON_H
#define COMMON_H

struct guid_s {
  unsigned int   part1;
  unsigned short part2;
  unsigned short part3;
  unsigned char  part4[8];
};

typedef struct guid_s guid_t;

struct rfid_object_s {
  char   enabled;
  guid_t id;
  short  pin;
};

typedef struct rfid_object_s rfid_object_t;

void init_obj(rfid_object_t *obj, int base);
void init_pins(short pins[5]);

int compare_guid(guid_t *id1, guid_t *id2);
int find(guid_t *id);

#endif
