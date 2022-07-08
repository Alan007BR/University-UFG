#include <stdio.h>
 
 
typedef struct {
 
    int cod;//cod do curso
    float cred;//valor por creditos
    char name[100];//Nome curso
 
   //Nome aluno
  //código do curso do Aluno
// creditos que ele está cursando
 
} University;
 
 
typedef struct { 
 
    char name[500];//Nome do aluno
    int cod;//código do curso do Aluno
    int cred;// creditos que ele está cursando
 
} Student;
 
int main() {
 
    int i = 0, j = 0;
    int n, m;
    double mensality;
    University *university = NULL;
    Student *student = NULL;
 
 
    scanf("%d", &n);
 
    university = calloc(n, sizeof(University));
 
    for(i = 0; i < n; i++) {
        scanf("%d\n", &university[i].cod);
        scanf("%f\n", &university[i].cred);
        scanf("%[^\n]%*c", &university[i].name);
    }
 
    scanf("%d\n", &m);
 
    student = calloc(m, sizeof(Student));
    
 
    for(i = 0; i < m; i++) {
        scanf("%[^\n]%*c", &student[i].name);
        scanf("%d", &student[i].cod);
        scanf("%d%*c", &student[i].cred);
    }
 
    for(i = 0; i < m; i++){
 
        for(j = 0; j < n; j++) {
            if (university[j].cod == student[i].cod) {
                mensality = (double)university[j].cred * (double)student[i].cred;
                printf("Aluno(a): %s Curso: %s Num. Creditos: %d Valor Credito: %.2lf Mensalidade: %.2lf\n", student[i].name, university[j].name, student[i].cred, university[j].cred, mensality);
                break;
            }
        }
    }
 
    return 0;
}