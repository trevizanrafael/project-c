#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int codigo_dis;
    char disciplina[100];
    float notas[4];
    float media;
} disciplina;

typedef struct
{
	int dia;
	int mes;
	int ano;
} data;

typedef struct {
    int ra;
    char nome[100];
    data matricula;
    char email[100];
    disciplina disciplinas[11];
} aluno;

int verifica_data(data *d) {
    if (d->mes < 1 || d->mes > 12) 
    {
        return 0;
    }

    int dias_no_mes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (d->ano % 4 == 0) 
    {
        dias_no_mes[2] = 29;
    }

    if (d->dia < 1 || d->dia > dias_no_mes[d->mes]) 
    {
        return 0;
    }

    return 1;
}

void cadastra_aluno (aluno alunos [], int dimensao) {
    int i, j, k;
    for (i = 0; i < dimensao; i++) 
    {
	printf("Digite o ra do aluno: ");
        scanf("%d", &alunos[i].ra);
        printf("Digite o nome do aluno: ");
        scanf(" %[^\n]", alunos[i].nome);
        
        for (j = 0; j < 4; j++) 
            { 
                printf("Digite a disciplina de número %d do aluno: ", j + 1);
                scanf(" %[^\n]", alunos[i].disciplinas[j].disciplina);
            }
        printf("Existem mais disciplinas a serem cadastradas? 0 para sim, 1 para não: ");
        scanf("%d", &k);
        int extra_j = j;
        while (k == 0) 
            {
                if (extra_j >= 10) 
                {
                    printf("Limite de disciplinas atingido!\n");
                    break;
                }
                printf("Digite a disciplina de número %d do aluno: ", extra_j + 1);
                scanf(" %[^\n]", alunos[i].disciplinas[extra_j].disciplina);
                extra_j++;
                printf("Existem mais disciplinas a serem cadastradas? 0 para sim, 1 para não: ");
                scanf("%d", &k);
            }
        printf("Digite o e-mail do aluno: ");
        scanf(" %[^\n]", alunos[i].email);
        
        printf("Digite a data de matrícula do aluno no formato DD/MM/YYYY: ");
        while (scanf("%d/%d/%d", &alunos[i].matricula.dia, &alunos[i].matricula.mes, &alunos[i].matricula.ano) != 3 || !verifica_data(&alunos[i].matricula)) {
            printf("Data inválida! Digite novamente no formato DD/MM/YYYY: ");
        }
    }
}

int main() {
    aluno alunos[1];
    cadastra_aluno(alunos, 1);
    return 0;
}
// oii
