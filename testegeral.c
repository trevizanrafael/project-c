#include <stdio.h>
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

int verifica_hora(hora *h) {
    if (h->hora > 23 || h->hora < 0 || h->min > 59 || h->min < 0) {
        return 0;
    }
    return 1;
}

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
    int ra_existente = 0; // variavel para verificar se o RA existe
    
    printf("Digite o RA do aluno: ");
    scanf("%d", &novo.aluno.ra);
    
    for (int i = 0; i < num_alunos; i++) 
        {
            if (alunos[i].ra == novo.aluno.ra) 
                {
                    novo.aluno = alunos[i]; // Copia os dados do aluno
                    ra_existente = 1;
                    break;
                }
        }
    if (!ra_existente) 
        {
            printf("Erro: RA não encontrado!\n");
            return; // Encerra a função sem cadastrar o compromisso
        }

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
            return; // Impede o cadastro do compromisso
        }

    printf("Digite a descrição do compromisso: ");
    scanf(" %[^\n]", novo.descricao);

    compromissos[*num_compromissos] = novo;
    (*num_compromissos)++;

    printf("Compromisso cadastrado com sucesso!\n");
}

int main(){
    aluno alunos[1]; // Um único aluno
    compromisso compromissos[10]; // Lista de compromissos (máx. 10 para teste)
    int num_compromissos = 0; // Contador de compromissos

    printf("=== Cadastro de Aluno ===\n");
    cadastra_aluno(alunos, 1);

    printf("\n=== Cadastro de Compromisso ===\n");
    cadastra_compromisso(compromissos, &num_compromissos, alunos, 1);

    printf("\n=== Dados Cadastrados ===\n");
    printf("Aluno: %s\n", alunos[0].nome);
    printf("RA: %d\n", alunos[0].ra);
    printf("E-mail: %s\n", alunos[0].email);
    printf("Data de matrícula: %02d/%02d/%04d\n", alunos[0].matricula.dia, alunos[0].matricula.mes, alunos[0].matricula.ano);

    printf("\nCompromisso do aluno %d - %s\n", compromissos[0].aluno.ra, compromissos[0].aluno.nome);
    printf("Data: %02d/%02d/%04d\n", compromissos[0].data.dia, compromissos[0].data.mes, compromissos[0].data.ano);
    printf("Horário: %02d:%02d\n", compromissos[0].horario.hora, compromissos[0].horario.min);
    printf("Descrição: %s\n", compromissos[0].descricao);
  return 0;
}
