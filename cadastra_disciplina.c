#include <stdio.h>
typedef struct{
        int codigo_dis;
        char disciplina[100];
        float notas[4];
        float media;
    } disciplina;

void cadastra_disciplina(disciplina disciplinas[], int num_disciplinas){
    int i;
    for(i=0;i<num_disciplinas;i++)
    {
        printf("Digite o código da disciplina: ");
        scanf("%d", &disciplinas[i].codigo_dis);
        printf("Digite o código da disciplina: ");
        scanf(" %[^\n]", disciplinas[i].disciplina); 
    }
}
int main() {
    disciplina disciplinas[1];
    cadastra_disciplina(disciplinas,1);
    return 0;
}
