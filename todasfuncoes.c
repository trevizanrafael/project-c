#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dis_cadastradas=0;

typedef struct
{
	int hora;
	int min;
} hora;

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

typedef struct {
    aluno aluno;
    hora horario;
    data data;
    char descricao[300];
} compromisso;

int verifica_data(data *d) {
    if (d->mes < 1 || d->mes > 12) 
    {
        return 0;
    } //ve se o mes ta fora dos 12
    
    int dias_no_mes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //define o numero de dias maximos pra cada mes

    if (d->ano % 4 == 0) 
    {
        dias_no_mes[2] = 29;
    } //define fevereiro como 29 caso seja um ano bissexto

    if (d->dia < 1 || d->dia > dias_no_mes[d->mes]) 
    {
        return 0;
    } // caso a data esteja fora dos dias retorna falso

    return 1; // retorna verdadeiro se passar nos testes
}

int verifica_hora(hora *h) {
    if (h->hora > 23 || h->hora < 0 || h->min > 59 || h->min < 0) {
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

int verifica_compromissos_do_dia(compromisso compromissos[], int num_compromissos, int ra, data d, hora h) {
    int count = 0; //inicializa o contador de compromissos
    for (int i = 0; i < num_compromissos; i++) 
    {
        if (compromissos[i].aluno.ra == ra &&
            compromissos[i].data.dia == d.dia &&
            compromissos[i].data.mes == d.mes &&
            compromissos[i].data.ano == d.ano) 
            {//caso já exista um compromisso no dia
                count++;//aumenta o contador de compromissos no dia
                if (compromissos[i].horario.hora == h.hora && compromissos[i].horario.min == h.min) //caso seja na mesma hora os dois compromissos
                    {
                        printf("Erro: O aluno já tem um compromisso nesse horário!\n");
                        return -1;
                    }
            }
    }
    if (count >= 2) 
        {//caso o contador dê 2, já existem dois compromissos cadastrados na data
            printf("Erro: O aluno já tem dois compromissos cadastrados nessa data!\n");
            return -1;
        }
    return 0; // sem problemas, pode cadastrar
}

void cadastra_compromisso(compromisso compromissos[], int *num_compromissos, aluno alunos[], int num_alunos) {
    if (*num_compromissos >= 100) 
        { // supondo um limite de 100 compromissos
            printf("Limite de compromissos atingido!\n");
            return;
        }
    compromisso novo; //declaracao do array do novo compromisso
    int ra_existente = 0; //variavel para verificar se o RA existe
    
    do {
        printf("Digite o RA do aluno: ");
        scanf("%d", &novo.aluno.ra);
        
        for (int i = 0; i < num_alunos; i++) 
            {
                if (alunos[i].ra == novo.aluno.ra) 
                    {
                        novo.aluno = alunos[i]; //copia os dados do aluno
                        ra_existente = 1;
                        break;
                    }
            }
        if (!ra_existente) 
            {
                printf("Erro: RA não encontrado! Digite novamente.\n");
            }
    } while (!ra_existente);

    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]", novo.aluno.nome);
    printf("Digite a data do compromisso (DD/MM/YYYY): ");
    while (scanf("%d/%d/%d", &novo.data.dia, &novo.data.mes, &novo.data.ano) != 3 || !verifica_data(&novo.data)) {
        printf("Data inválida! Digite novamente no formato DD/MM/YYYY: ");
    }
    printf("Digite o horário do compromisso (HH:MM): ");
    scanf("%d:%d", &novo.horario.hora, &novo.horario.min);
    if (verifica_compromissos_do_dia(compromissos, *num_compromissos, novo.aluno.ra, novo.data, novo.horario) == -1) 
        {
            return; //impede o cadastro do compromisso
        }
    printf("Digite a descrição do compromisso: ");
    scanf(" %[^\n]", novo.descricao);
    compromissos[*num_compromissos] = novo;
    (*num_compromissos)++;
    printf("Compromisso cadastrado com sucesso!\n");
}

int main(){
    int i=1;
    disciplina disciplinas[5];
    compromisso compromissos[10];
    aluno alunos[1];
    cadastra_disciplina(disciplinas,5);
    cadastra_aluno(alunos,1,disciplinas);
    cadastra_compromisso(compromissos, &i, alunos, 1);
    return 0;
}
