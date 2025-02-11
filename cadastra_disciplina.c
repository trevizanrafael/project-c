#include <stdio.h>
#include <string.h> 
int dis_cadastradas=0;
typedef struct
{
	int dia;
	int mes;
	int ano;
} data;

typedef struct{
    int codigo_dis;
    char disciplina[100];
    float notas[4];
    float media;
} disciplina;

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

void cadastra_disciplina(disciplina disciplinas[], int num_disciplinas){
    int i;
    for(i=0;i<num_disciplinas;i++)
    {
        printf("Digite o código da disciplina: ");
        scanf("%d", &disciplinas[i].codigo_dis);
        printf("Digite o nome da disciplina: ");
        scanf(" %[^\n]", disciplinas[i].disciplina); 
        dis_cadastradas++;
    }
}

void cadastra_aluno (aluno alunos [], int dimensao, disciplina disciplinas[]) {
    int i, j, k, l, m;
    for (i = 0; i < dimensao; i++) 
    {
        printf("Digite o ra do aluno: ");
        scanf("%d", &alunos[i].ra);
        
        printf("Digite o nome do aluno: ");
        scanf(" %[^\n]", alunos[i].nome);
        
        for (j = 0; j < 4; j++) 
        {
            int verifica_dis;
            do 
            {
                verifica_dis = 0;
                printf("Digite a disciplina de número %d do aluno: ", j + 1);
                scanf(" %[^\n]", alunos[i].disciplinas[j].disciplina);
                for(m = 0; m < dis_cadastradas; m++) 
                {
                    if(strcmp(alunos[i].disciplinas[j].disciplina, disciplinas[m].disciplina) == 0) 
                    {
                        verifica_dis = 1;
                        alunos[i].disciplinas[j].codigo_dis = disciplinas[m].codigo_dis;
                        break;
                    }
                }
                if(!verifica_dis) 
                {
                    printf("Disciplina não cadastrada! Tente novamente.\n");
                }
            } while(!verifica_dis);
            for(l = 0; l < 4; l++) 
            {
                printf("     Digite a nota de número %d da disciplina de número %d do aluno: ", l + 1, j + 1);
                scanf("%f", &alunos[i].disciplinas[j].notas[l]);
            }
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
            
            int verifica_dis;
            do 
            {
                verifica_dis = 0;
                printf("Digite a disciplina de número %d do aluno: ", extra_j + 1);
                scanf(" %[^\n]", alunos[i].disciplinas[extra_j].disciplina);
                for(m = 0; m < dis_cadastradas; m++) 
                {
                    if(strcmp(alunos[i].disciplinas[extra_j].disciplina, disciplinas[m].disciplina) == 0) 
                    {
                        verifica_dis = 1;
                        alunos[i].disciplinas[extra_j].codigo_dis = disciplinas[m].codigo_dis;
                        break;
                    }
                }
                if(!verifica_dis) 
                {
                    printf("Disciplina não cadastrada! Tente novamente.\n");
                }
            } while(!verifica_dis);
            for(l = 0; l < 4; l++) 
            {
                printf("     Digite a nota de número %d da disciplina de número %d do aluno: ", l + 1, extra_j + 1);
                scanf("%f", &alunos[i].disciplinas[extra_j].notas[l]);
            }
            
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
    disciplina disciplinas[5];
    cadastra_disciplina(disciplinas,5);
    cadastra_aluno(alunos,1,disciplinas);
    return 0;
}
