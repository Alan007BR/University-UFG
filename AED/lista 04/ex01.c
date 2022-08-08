#include <stdio.h>



typedef struct Paciente{
    int h, m, c;

}Paciente;

typedef struct Fila{
    Paciente p[50];  // como o exercício da uma quantidade máxima, nào é necessário alocação dinâmica.
    int front, rear;
} Fila;

typedef struct Horas{
    int h, m;
} Horas;

void preencher(Paciente *p, int h, int m, int c) {
    p->h = h; p->m = m; p->c = c;
}

void insert(Paciente *p, Fila *fila){
    if(fila->rear == 50-1){
        fila->rear = 0;
    }else{
        (fila->rear)++;
    }

    if(fila->rear == fila->front){
        return 0;
    }

    fila->p[fila->rear].h = p->h;
    fila->p[fila->rear].m = p->m;
    fila->p[fila->rear].c = p->c;

    return;
}

void atualizahora(Horas *hora, int x){
    hora->m += x;
    if(hora->m >=60){
        (hora->h)++;
        hora->m = 0;
    }
}

void critic(Fila *fila, int i){
    fila->p[i].m += fila->p[i].c;
    if(fila->p[i].m >=60){
        (fila->p[i].h)++;
        fila->p[i].m = 0;
    }

}

int main(){

    int nTri, i = 0;
    Paciente p;
    Fila fila;
    Horas hora;
    int h, m, c, x = 2;
    fila.front = fila.rear = 50-1;
    int crit = 0;

    scanf("%d",&nTri);

    for(i = 0; i < nTri; i++){
        scanf("%d %d %d", &h, &m, &c);
        preencher(&p, h, m, c);
        insert(&p, &fila);
    }
    hora.h = fila.p[0].h;
    hora.m = fila.p[0].m;

    for(i = 1; i < nTri; i++){
        atualizahora(&hora, 30);
        //printf("p(%d) %d:%d\n", i+1, hora.h, hora.m);
        critic(&fila, i);
        //printf("c(%d) %d:%d\n", i+1, fila.p[i].h, fila.p[i].m);

        if(hora.m > fila.p[i].m && hora.h == fila.p[i].h || hora.m <= fila.p[i].m && hora.h > fila.p[i].h) {
            crit++;
        }
    }

    printf("%d\n", crit);


    return 0;
}