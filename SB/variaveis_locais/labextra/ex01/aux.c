#include <stdlib.h>

#include <stdio.h>



#include "aux.h"



void readObject(struct Object *ptr, int *id)

{

  char buf[16];

  printf("Digite o ID: ");

  fgets(buf, 16, stdin);

  sscanf(buf, "%ld", &ptr->ID);

  *id = ptr->ID;

  printf("Digite o nome: ");

  fgets(buf, 16, stdin);

  sscanf(buf, "%s", ptr->name);

}



void readPerson(struct Person *ptr, int *id)

{

  char buf[16];

  printf("Reading person\n");

  ptr->type = 1;

  readObject((struct Object*)ptr, id);

  printf("Digite a idade: ");

  fgets(buf, 16, stdin);

  sscanf(buf, "%d", &ptr->age);

}



void readCar(struct Car *ptr, int *id)

{

  char buf[16];

  printf("Reading car\n");

  ptr->type = 2;

  readObject((struct Object*)ptr, id);

  printf("Digite a cor: ");

  fgets(buf, 16, stdin);

  sscanf(buf, "%s", ptr->color);

}