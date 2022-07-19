#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define MENOR -1
#define IGUAL 0
#define MAIOR 1

typedef struct Data {
    unsigned int dia;
    unsigned int mes;
    unsigned int ano;
} Data;

Data *criaData                  (unsigned int dia, unsigned int mes, unsigned int ano);
Data *copiaData                 (Data d);
void liberaData                 (Data * d);
Data *somaDiasData              (Data d, unsigned int dias);
Data *subtrairDiasData          (Data d, unsigned int dias);
void atribuirData               (Data * d, unsigned int dia, unsigned int mes, unsigned int ano);
unsigned int obtemDiaData       (Data d);
unsigned int obtemMesData       (Data d);
unsigned int obtemAnoData       (Data d);
unsigned int bissextoData       (Data d);
int comparaData                 (Data d1, Data d2);
unsigned int numeroDiasDatas    (Data d1, Data d2);
unsigned int numeroMesesDatas   (Data d1, Data d2);
unsigned int numeroAnosDatas    (Data d1, Data d2);
unsigned int obtemDiaSemanaData (Data d);
char *imprimeData               (Data d, char *formato);