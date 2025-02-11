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
    disciplina disciplinas[];
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

compromisso* realocar_compromissos(compromisso *compromissos, int tamanho_atual, int novoTamanho) {
    compromisso *temp = (compromisso*) realloc(compromissos, novoTamanho * sizeof(compromisso));
    if (temp == NULL) {
        printf("Erro ao realocar memória para compromissos!\n");
        free(compromissos); // Libera a memória alocada anteriormente
        exit(1); // Encerra o programa em caso de falha na realocação
    }
    return temp;
}

compromisso* alocar_compromissos(int tamanho_inicial) {
    compromisso *compromissos = (compromisso*) malloc(tamanho_inicial * sizeof(compromisso));
    if (compromissos == NULL) {
        printf("Erro ao alocar memória para compromissos!\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    }
    return compromissos;
}

aluno* realocar_alunos(aluno *alunos, int tamanho_atual, int novoTamanho) {
    aluno *temp = (aluno*) realloc(alunos, novoTamanho * sizeof(aluno));
    if (temp == NULL) {
        printf("Erro ao realocar memória para alunos!\n");
        free(alunos); // Libera a memória alocada anteriormente
        exit(1); // Encerra o programa em caso de falha na realocação
    }
    return temp;
}

aluno* alocar_alunos(int tamanho_inicial) {
    aluno *alunos = (aluno*) malloc(tamanho_inicial * sizeof(aluno));
    if (alunos == NULL) {
        printf("Erro ao alocar memória para alunos!\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    }
    return alunos;
}

disciplina* alocar_disciplinas(int tamanho_inicial) {
    disciplina *disciplinas = (disciplina*) malloc(tamanho_inicial * sizeof(disciplina));
    if (disciplinas == NULL) {
        printf("Erro ao alocar memória para disciplinas!\n");
        exit(1); // Encerra o programa em caso de falha na alocação
    }
    return disciplinas;
}

disciplina* realocar_disciplinas(disciplina *disciplinas, int tamanho_atual, int novoTamanho) {
    disciplina *temp = (disciplina*) realloc(disciplinas, novoTamanho * sizeof(disciplina));
    if (temp == NULL) {
        printf("Erro ao realocar memória para disciplinas!\n");
        free(disciplinas); // Libera a memória alocada anteriormente
        exit(1); // Encerra o programa em caso de falha na realocação
    }
    return temp;
}

void cadastra_disciplina(disciplina **disciplinas, int *num_disciplinas, int *tamanho_disciplinas){
    int i;
    if (*num_disciplinas >= *tamanho_disciplinas) 
    {
        *tamanho_disciplinas*=2; //dobra o tamanho da memoria para passar de parametro para realloc
        *disciplinas=realocar_disciplinas(*disciplinas, *num_disciplinas, *tamanho_disciplinas);
    }
    printf("Digite o código da disciplina: ");
    scanf("%d", &(*disciplinas)[*num_disciplinas].codigo_dis);
    printf("Digite o nome da disciplina: ");
    scanf(" %[^\n]", (*disciplinas)[*num_disciplinas].disciplina); 
    (*num_disciplinas)++;
    dis_cadastradas++;
}

void cadastra_aluno (aluno **alunos, int *num_alunos, int *tamanho_alunos, disciplina disciplinas[]) {
    int i, j, k, l, m;
    //verifica se há memoria
    if (*num_alunos>=*tamanho_alunos) 
    {
        *tamanho_alunos*=2; //dobra o tamanho
        *alunos=realocar_alunos(*alunos, *num_alunos, *tamanho_alunos);
    }
    i=*num_alunos;
        printf("Digite o ra do aluno: ");
        scanf("%d", &(*alunos)[i].ra);
        
        printf("Digite o nome do aluno: ");
        scanf(" %[^\n]", (*alunos)[i].nome);
        
        for (j = 0; j < 4; j++) 
        {
            int verifica_dis;
            do 
            {
                verifica_dis = 0;
                printf("Digite a disciplina de número %d do aluno: ", j + 1);
                scanf(" %[^\n]", (*alunos)[i].disciplinas[j].disciplina);
                for(m = 0; m < dis_cadastradas; m++) 
                {
                    if(strcmp((*alunos)[i].disciplinas[j].disciplina, disciplinas[m].disciplina) == 0) 
                    {
                        verifica_dis = 1;
                        (*alunos)[i].disciplinas[j].codigo_dis = disciplinas[m].codigo_dis;
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
                scanf("%f", &(*alunos)[i].disciplinas[j].notas[l]);
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
                scanf(" %[^\n]", (*alunos)[i].disciplinas[extra_j].disciplina);
                for(m = 0; m < dis_cadastradas; m++) 
                {
                    if(strcmp((*alunos)[i].disciplinas[extra_j].disciplina, disciplinas[m].disciplina) == 0) 
                    {
                        verifica_dis = 1;
                        (*alunos)[i].disciplinas[extra_j].codigo_dis = disciplinas[m].codigo_dis;
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
                scanf("%f", &(*alunos)[i].disciplinas[extra_j].notas[l]);
            }
            
            extra_j++;
            printf("Existem mais disciplinas a serem cadastradas? 0 para sim, 1 para não: ");
            scanf("%d", &k);
        }
        
        printf("Digite o e-mail do aluno: ");
        scanf(" %[^\n]", (*alunos)[i].email);
        
        printf("Digite a data de matrícula do aluno no formato DD/MM/YYYY: ");
        while (scanf("%d/%d/%d", &(*alunos)[i].matricula.dia, &(*alunos)[i].matricula.mes, &(*alunos)[i].matricula.ano) != 3 || !verifica_data(&(*alunos)[i].matricula)) 
        {
            printf("Data inválida! Digite novamente no formato DD/MM/YYYY: ");
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

void cadastra_compromisso(compromisso **compromissos, int *num_compromissos, int *tamanho_compromissos, aluno alunos[], int num_alunos) {
    if (*num_compromissos >= 100) 
        { // supondo um limite de 100 compromissos
            printf("Limite de compromissos atingido!\n");
            return;
        }
    //ve se tem memória
    if (*num_compromissos>=*tamanho_compromissos) 
    {
        *tamanho_compromissos*=2; // Dobra o tamanho
        *compromissos=realocar_compromissos(*compromissos, *num_compromissos, *tamanho_compromissos);
    }
    compromisso novo; //declaracao do array do novo compromisso
    int ra_existente=0; //variavel para verificar se o RA existe
    
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
    while (scanf("%d/%d/%d", &novo.data.dia, &novo.data.mes, &novo.data.ano) != 3 || !verifica_data(&novo.data)) 
    {
        printf("Data inválida! Digite novamente no formato DD/MM/YYYY: ");
    }
    
    printf("Digite o horário do compromisso (HH:MM): ");
    while(scanf("%d:%d", &novo.horario.hora, &novo.horario.min) != 2 || !verifica_hora(&novo.horario))
    {
        printf("Hora inválida! Digite novamente no formato (HH:MM): ");
    }
    
    //verificação se há compromisso no dia
    if (verifica_compromissos_do_dia(*compromissos, *num_compromissos, novo.aluno.ra, novo.data, novo.horario) == -1)
        {
            printf("Impossível cadastrar nesse dia e nessa data.");
            return; //impede o cadastro do compromisso
        }
        
    printf("Digite a descrição do compromisso: ");
    scanf(" %[^\n]", novo.descricao);
    
    (*compromissos)[*num_compromissos] = novo; //adiciona o novo compromisso
    (*num_compromissos)++;
    printf("Compromisso cadastrado com sucesso!\n");
}

void exibir_menu() {
    printf("=========================================\n");
    printf("      MENU DE CADASTRO E RELATÓRIOS\n");
    printf("=========================================\n");
    printf("1 - Cadastrar Disciplina\n");
    printf("2 - Cadastrar Aluno\n");
    printf("3 - Cadastrar Compromisso\n");
    printf("4 - Imprimir Compromissos\n");
    printf("    a - De um Aluno (ordenado por data e hora)\n");
    printf("    b - De todos os Alunos (ordenado por RA, data e hora)\n");
    printf("    c - De uma Data (ordenado por hora e RA)\n");
    printf("    d - De todas as Datas (ordenado por data, hora e RA)\n");
    printf("5 - Imprimir Dados de um Aluno\n");
    printf("6 - Imprimir Dados de Todos os Alunos (ordenado por RA)\n");
    printf("7 - Sair\n");
    printf("===============================\n");
    printf("Escolha uma opção: ");
}

int main(){
        int num_alunos=0;
        int num_compromissos=0;
        int tamanho_alunos=10;
        int tamanho_compromissos=10;
        int num_disciplinas=0;
        int tamanho_disciplinas=10;
        
        aluno *alunos = alocar_alunos(tamanho_alunos);
        compromisso *compromissos = alocar_compromissos(tamanho_compromissos);
        disciplina *disciplinas = alocar_disciplinas(tamanho_disciplinas);
    
    int decisao=0;
    do
    {
    exibir_menu();
    scanf("%d",&decisao);
        switch(decisao)
    {
        case 7:
            return 0;
        case 1:
            printf("i\n");
            break;
        default:
            printf("Número não representa uma ação.\n");
    }
    } while(decisao!=7);
    
    free(alunos);
    free(compromissos);
    free(disciplinas);
    return 0;
}
