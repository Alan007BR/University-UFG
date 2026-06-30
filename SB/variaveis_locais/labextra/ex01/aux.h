#ifndef AUX_H
#define AUX_H

struct Object {
  int  type;
  long ID;
  char name[16];
};

struct Person {
  int  type;
  long ID;
  char name[16];
  int age;
};

struct Car {
  int  type;
  long ID;
  char name[16];
  char color[8];
};

void readPerson(struct Person *ptr, int *id);
void readCar(struct Car *ptr, int *id);

#endif