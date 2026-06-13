#include <stdlib.h>
#include <stdio.h>
#include "aux.h"


void showPerson(struct Person *person);
void showCar(struct Car *car);


void reader(long verbose){

  int id1, id2, id3;
  struct Person p;
  struct Car c[2];

  readPerson(&p, &id1);
  readCar(&c[0], &id2);
  readCar(&c[1], &id3);

  if (verbose) {
     printf("id1 = %d, id2 = %d, id3 = %d\n", id1, id2, id3);
     printf("Person ID: %ld\n", p.ID);
     printf("Car ID: %ld\n", c[0].ID);
     printf("Car ID: %ld\n", c[1].ID);
  }

  showPerson(&p);
  showCar(&c[0]);
  showCar(&c[1]);
}

void showPerson(struct Person *person)
{
  printf("tipo = %d, ID = %ld, nome = '%s', idade = %d\n",
    person->type, person->ID, person->name, person->age);
}

void showCar(struct Car *car)
{
  printf("tipo = %d, ID = %ld, nome = '%s', cor = '%s'\n",
    car->type, car->ID, car->name, car->color);
}

