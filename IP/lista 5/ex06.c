#include <stdio.h>
#include <string.h>


typedef struct {

    int dia;
    int mes;
    int ano;

} Data;

typedef struct {

    int matricula;
    Data nascimento;
    char nome[200];

} Aluno;

int comparaData(Data a, Data b) {
    if(a.ano < b.ano) return 1;
    else if(a.ano == b.ano) {
        if(a.mes < b.mes) return 1;
        else if(a.mes == b.mes) {
            if(a.dia <= b.dia) return 1;
        }
    }

    return 0;
}

void ordenaAlunos(Aluno * vet, int final) {
    int i = 0, j = 0;
    int novo;
    Aluno tmp;

    for(i = 0; i < final - 1; i++) {
        novo = i;

        for(j = i+1; j < final; j++) {
            if(comparaData(vet[j].nascimento, vet[novo].nascimento) == 0) novo = j;
        }

        if(novo != i) {
            tmp = vet[i];
            vet[i] = vet[novo];
            vet[novo] = tmp;
        }
    }
}

int main() {

    int nalunos;
    int i = 0;
    Aluno *alunos = NULL;

    scanf("%d", &nalunos);

    alunos = calloc(nalunos, sizeof(Aluno));

    for(i = 0; i < nalunos; i++) {
        scanf("%d %d %d %d %[^\n]", &alunos[i].matricula, &alunos[i].nascimento.dia, &alunos[i].nascimento.mes, &alunos[i].nascimento.ano, alunos[i].nome );

    }

    ordenaAlunos(alunos, nalunos);

    for(i = 0; i < nalunos; i++) {
    printf("Matric.: %d Nome: %s Data Nasc: %d/%d/%d\n", alunos[i].matricula, alunos[i].nome, alunos[i].nascimento.dia, alunos[i].nascimento.mes, alunos[i].nascimento.ano);
    }

    free(alunos);

    return 0;
}