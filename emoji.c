#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dis_cadastradas=15;
int numero_alunos=4;

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
    int i, j, k, l, m, media1=0;
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
            (*alunos)[i].disciplinas[extra_j].media=media1/4;
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
        numero_alunos++;
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
        
        for (int i = 0; i < numero_alunos; i++) 
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
            printf("Impossível cadastrar nesse horário do dia.\n");
            return; //impede o cadastro do compromisso
        }
        
    printf("Digite a descrição do compromisso: ");
    scanf(" %[^\n]", novo.descricao);
    
    (*compromissos)[*num_compromissos] = novo; //adiciona o novo compromisso
    (*num_compromissos)++;
    printf("Compromisso cadastrado com sucesso!\n");
}

//precisei de ia para aprender a usar qsort da biblioteca stlib, pois nao sabia como ela era usada
int compara_compromissos(const void *a, const void *b) {
    const compromisso *comp1 = (const compromisso *)a;
    const compromisso *comp2 = (const compromisso *)b;

    // Comparar datas
    if (comp1->data.ano != comp2->data.ano) 
    {
        return comp1->data.ano - comp2->data.ano;
    }
    if (comp1->data.mes != comp2->data.mes) 
    {
        return comp1->data.mes - comp2->data.mes;
    }
    if (comp1->data.dia != comp2->data.dia) 
    {
        return comp1->data.dia - comp2->data.dia;
    }

    // datas iguais, ver hora
    if (comp1->horario.hora != comp2->horario.hora) 
    {
        return comp1->horario.hora - comp2->horario.hora;
    }
    return comp1->horario.min - comp2->horario.min;
}

void imprime_compromissos_aluno(compromisso compromissos[], int num_compromissos, int ra) {
    compromisso *compromissos_aluno = malloc(num_compromissos * sizeof(compromisso));
    int count = 0, i;

    // Filtra os compromissos do aluno
    for (i = 0; i < num_compromissos; i++) 
    {
        if (compromissos[i].aluno.ra == ra) 
        {
            compromissos_aluno[count++] = compromissos[i];
        }
    }
    
    qsort(compromissos_aluno, count, sizeof(compromisso), compara_compromissos);

    printf("Compromissos do aluno (RA: %d):\n", ra);
    for (int i = 0; i < count; i++) 
    {
        printf("Data: %02d/%02d/%04d - Horário: %02d:%02d - Descrição: %s\n",
               compromissos_aluno[i].data.dia,
               compromissos_aluno[i].data.mes,
               compromissos_aluno[i].data.ano,
               compromissos_aluno[i].horario.hora,
               compromissos_aluno[i].horario.min,
               compromissos_aluno[i].descricao);
    }

    free(compromissos_aluno);
}

int compara_compromissos_geral(const void *a, const void *b) {
    const compromisso *comp1 = (const compromisso *)a;
    const compromisso *comp2 = (const compromisso *)b;

    // Comparar RA
    if (comp1->aluno.ra != comp2->aluno.ra) 
    {
        return comp1->aluno.ra - comp2->aluno.ra;
    }

    // Comparar datas
    if (comp1->data.ano != comp2->data.ano) 
    {
        return comp1->data.ano - comp2->data.ano;
    }
    if (comp1->data.mes != comp2->data.mes) 
    {
        return comp1->data.mes - comp2->data.mes;
    }
    if (comp1->data.dia != comp2->data.dia) 
    {
        return comp1->data.dia - comp2->data.dia;
    }

    // Comparar horas
    if (comp1->horario.hora != comp2->horario.hora) 
    {
        return comp1->horario.hora - comp2->horario.hora;
    }
    return comp1->horario.min - comp2->horario.min;
}

void imprime_todos_compromissos(compromisso compromissos[], int num_compromissos) {
    // Ordena os compromissos usando qsort
    qsort(compromissos, num_compromissos, sizeof(compromisso), compara_compromissos_geral);

    printf("Compromissos de todos os alunos (ordenados por RA, Data e Hora):\n");
    for (int i = 0; i < num_compromissos; i++) 
    {
        printf("RA: %d - Data: %02d/%02d/%04d - Horário: %02d:%02d - Descrição: %s\n",
               compromissos[i].aluno.ra,
               compromissos[i].data.dia,
               compromissos[i].data.mes,
               compromissos[i].data.ano,
               compromissos[i].horario.hora,
               compromissos[i].horario.min,
               compromissos[i].descricao);
    }
}

int compara_compromissos_por_hora_e_ra(const void *a, const void *b) {
    const compromisso *comp1 = (const compromisso *)a;
    const compromisso *comp2 = (const compromisso *)b;

    // Comparar horas
    if (comp1->horario.hora != comp2->horario.hora) 
    {
        return comp1->horario.hora - comp2->horario.hora;
    }
    if (comp1->horario.min != comp2->horario.min) 
    {
        return comp1->horario.min - comp2->horario.min;
    }

    // Se as horas forem iguais, comparar RA
    return comp1->aluno.ra - comp2->aluno.ra;
}

// Função para imprimir compromissos de uma data específica
void imprime_compromissos_por_data(compromisso compromissos[], int num_compromissos, data d) {
    compromisso *compromissos_data = malloc(num_compromissos * sizeof(compromisso));
    int count = 0;

    // Filtra os compromissos pela data
    for (int i = 0; i < num_compromissos; i++) 
    {
        if (compromissos[i].data.dia == d.dia &&
            compromissos[i].data.mes == d.mes &&
            compromissos[i].data.ano == d.ano) {
            compromissos_data[count++] = compromissos[i];
        }
    }

    // Ordena os compromissos filtrados usando qsort
    qsort(compromissos_data, count, sizeof(compromisso), compara_compromissos_por_hora_e_ra);

    // Imprime os compromissos
    printf("Compromissos na data %02d/%02d/%04d (ordenados por Hora e RA):\n", d.dia, d.mes, d.ano);
    for (int i = 0; i < count; i++) 
    {
        printf("RA: %d - Horário: %02d:%02d - Descrição: %s\n",
               compromissos_data[i].aluno.ra,
               compromissos_data[i].horario.hora,
               compromissos_data[i].horario.min,
               compromissos_data[i].descricao);
    }

    free(compromissos_data);
}

int compara_compromissos_d(const void *a, const void *b) {
    const compromisso *comp1 = (const compromisso *)a;
    const compromisso *comp2 = (const compromisso *)b;

    // Comparar datas
    if (comp1->data.ano != comp2->data.ano) 
    {
        return comp1->data.ano - comp2->data.ano;
    }
    if (comp1->data.mes != comp2->data.mes) 
    {
        return comp1->data.mes - comp2->data.mes;
    }
    if (comp1->data.dia != comp2->data.dia) 
    {
        return comp1->data.dia - comp2->data.dia;
    }

    // Se as datas forem iguais, comparar horas
    if (comp1->horario.hora != comp2->horario.hora) 
    {
        return comp1->horario.hora - comp2->horario.hora;
    }
    if (comp1->horario.min != comp2->horario.min) 
    {
        return comp1->horario.min - comp2->horario.min;
    }

    // Se as horas forem iguais, comparar RA
    return comp1->aluno.ra - comp2->aluno.ra;
}

// Função para imprimir todos os compromissos
void imprime_todos_compromissos_d(compromisso compromissos[], int num_compromissos) {
    // Ordena os compromissos usando qsort
    qsort(compromissos, num_compromissos, sizeof(compromisso), compara_compromissos);

    // Imprime os compromissos
    printf("Compromissos (ordenados por Data, Hora e RA):\n");
    for (int i = 0; i < num_compromissos; i++) 
    {
        printf("Data: %02d/%02d/%04d - RA: %d - Horário: %02d:%02d - Descrição: %s\n",
               compromissos[i].data.dia,
               compromissos[i].data.mes,
               compromissos[i].data.ano,
               compromissos[i].aluno.ra,
               compromissos[i].horario.hora,
               compromissos[i].horario.min,
               compromissos[i].descricao);
    }
}

void imprime_dados_aluno(aluno alunos[], int num_alunos, int ra) {
    for (int i = 0; i < numero_alunos; i++) {
        if (alunos[i].ra == ra) {
            printf("Dados do Aluno:\n");
            printf("RA: %d\n", alunos[i].ra);
            printf("Nome: %s\n", alunos[i].nome);
            printf("E-mail: %s\n", alunos[i].email);
            printf("Data de Matrícula: %02d/%02d/%04d\n", alunos[i].matricula.dia, alunos[i].matricula.mes, alunos[i].matricula.ano);
            // Imprime as disciplinas, notas e média
            printf("Disciplinas:\n");
            for (int j = 0; j < dis_cadastradas; j++) 
            { 
                if(alunos[i].disciplinas[j].codigo_dis==0)
                {
                    break;
                }
                printf("  Disciplina: %s (Código: %d)\n", alunos[i].disciplinas[j].disciplina, alunos[i].disciplinas[j].codigo_dis);
                printf("    Notas: ");
                float soma=0;
                for (int k = 0; k < 4; k++) 
                { 
                    printf("%.2f ", alunos[i].disciplinas[j].notas[k]);
                    soma+=alunos[i].disciplinas[j].notas[k];
                }
                printf("\n    Média: %.2f\n", soma/4.0);
            }
            return; // Aluno encontrado, sai da função
        }
    }
    printf("Aluno com RA %d não encontrado.\n", ra);
}

int compara_alunos(const void *a, const void *b) {
    const aluno *aluno1 = (const aluno *)a;
    const aluno *aluno2 = (const aluno *)b;
    return aluno1->ra - aluno2->ra; // Ordena por RA
}

void imprime_dados_todos_alunos(aluno alunos[], int num_alunos) {
    // Ordena os alunos usando qsort
    qsort(alunos, num_alunos, sizeof(aluno), compara_alunos);

    // Imprime os dados dos alunos
    printf("Dados de Todos os Alunos (ordenados por RA):\n");
    for (int i = 0; i < num_alunos; i++) {
        printf("RA: %d\n", alunos[i].ra);
        printf("Nome: %s\n", alunos[i].nome);
        printf("E-mail: %s\n", alunos[i].email);
        printf("Data de Matrícula: %02d/%02d/%04d\n", alunos[i].matricula.dia, alunos[i].matricula.mes, alunos[i].matricula.ano);
        
        // Imprime as disciplinas, notas e média
        printf("Disciplinas:\n");
        for (int j = 0; j < dis_cadastradas; j++) 
        {
        if(alunos[i].disciplinas[j].codigo_dis==0)
            {
                break;
            }
            printf("  Disciplina: %s (Código: %d)\n", alunos[i].disciplinas[j].disciplina, alunos[i].disciplinas[j].codigo_dis);
            printf("    Notas: ");
            float soma1=0;
            for (int k = 0; k < 4; k++) 
            { 
                printf("%.2f ", alunos[i].disciplinas[j].notas[k]);
                soma1=soma1+alunos[i].disciplinas[j].notas[k];
            }
            printf("\n    Média: %.2f\n",soma1/4.0);
        }
        printf("--------------------------------------------------------\n");
    }
}

void exibir_menu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════╗\n");
    printf("║       🎓 MENU DE CADASTRO E RELATÓRIOS 📋               ║\n");
    printf("╠════════════════════════════════════════════════╣\n");
    printf("║  1️⃣  Cadastrar Disciplina                              ║\n");
    printf("║  2️⃣  Cadastrar Aluno                                   ║\n");
    printf("║  3️⃣  Cadastrar Compromisso                             ║\n");
    printf("║  4️⃣  📆 Imprimir Compromissos                          ║\n");
    printf("║     ├── 🧑‍🎓 a) De um Aluno (por data e hora)         ║\n");
    printf("║     ├── 👨‍🎓 b) De todos os Alunos (RA, data e hora)  ║\n");
    printf("║     ├── 📅 c) De uma Data (por hora e RA)              ║\n");
    printf("║     ├── 🗓️ d) De todas as Datas (data, hora e RA)      ║\n");
    printf("║  5️⃣  📖 Imprimir Dados de um Aluno                     ║\n");
    printf("║  6️⃣  📚 Imprimir Dados de Todos os Alunos              ║\n");
    printf("║  7️⃣  ❌ Sair                                           ║\n");
    printf("╚════════════════════════════════════════════════╝\n");
    printf("➡ Escolha uma opção: ");
}

void exibir_submenu_compromissos() {
    printf("\n=================================================\n");
    printf("       OPCOES DE IMPRESSAO DE COMPROMISSOS\n");
    printf("=================================================\n");
    printf("a) De um Aluno           (ordenado por Data e Hora)\n");
    printf("b) De todos os Alunos    (ordenado por RA, Data e Hora)\n");
    printf("c) De uma Data           (ordenado por Hora e RA)\n");
    printf("d) De todas as Datas     (ordenado por Data, Hora e RA)\n");
    printf("e) Voltar ao menu principal\n");
    printf("==========================================\n");
    printf("Escolha uma opcao: ");
}

int main(){
        int num_alunos=0;
        int num_compromissos=0;
        int tamanho_alunos=10;
        int tamanho_compromissos=10;
        int num_disciplinas=0;
        int tamanho_disciplinas=16;
        
        aluno *alunos = alocar_alunos(tamanho_alunos);
        
        alunos[num_alunos++] = (aluno){123, "Rafael", {15, 3, 2023}, "rafa@example.com"};
        alunos[0].disciplinas[0] = (disciplina){101, "Matemática", {7.0, 8.5, 9.0, 6.5}, 7.75};
        alunos[0].disciplinas[1] = (disciplina){102, "Física", {6.0, 7.5, 8.0, 5.5}, 6.75};
        alunos[0].disciplinas[2] = (disciplina){103, "Química", {8.0, 9.0, 7.5, 8.5}, 8.25};
        alunos[0].disciplinas[3] = (disciplina){104, "Biologia", {9.0, 8.0, 9.5, 10.0}, 9.13};
        alunos[0].disciplinas[4] = (disciplina){105, "História", {7.5, 6.5, 8.0, 7.0}, 7.25};
        
        alunos[num_alunos++] = (aluno){456, "Gabriel", {14, 3, 2023}, "gabs@example.com"};
        alunos[1].disciplinas[0] = (disciplina){101, "Matemática", {8.0, 7.0, 9.0, 8.5}, 8.13};
        alunos[1].disciplinas[1] = (disciplina){102, "Física", {5.5, 6.0, 7.0, 6.5}, 6.25};
        alunos[1].disciplinas[2] = (disciplina){103, "Química", {9.0, 8.5, 9.5, 10.0}, 9.25};
        alunos[1].disciplinas[3] = (disciplina){104, "Biologia", {7.0, 6.5, 8.0, 7.5}, 7.00};
        alunos[1].disciplinas[4] = (disciplina){105, "História", {8.5, 9.0, 8.0, 7.5}, 8.25};
        
        alunos[num_alunos++] = (aluno){789, "Nicolly", {16, 3, 2023}, "nika@example.com"};
        alunos[2].disciplinas[0] = (disciplina){101, "Matemática", {9.5, 8.0, 9.0, 10.0}, 9.38};
        alunos[2].disciplinas[1] = (disciplina){102, "Física", {7.0, 8.0, 6.5, 7.5}, 7.25};
        alunos[2].disciplinas[2] = (disciplina){103, "Química", {8.0, 9.0, 8.5, 9.5}, 8.75};
        alunos[2].disciplinas[3] = (disciplina){104, "Biologia", {6.5, 7.0, 8.0, 7.5}, 7.25};
        alunos[2].disciplinas[4] = (disciplina){105, "História", {9.0, 8.5, 9.5, 10.0}, 9.25};
        
        
        compromisso *compromissos = alocar_compromissos(tamanho_compromissos);
        compromissos[num_compromissos++] = (compromisso){alunos[0], {10, 0}, {20, 2, 2025}, "Reunião com o professor"};
        compromissos[num_compromissos++] = (compromisso){alunos[1], {14, 0}, {21, 2, 2025}, "Entrega de trabalho"};
        compromissos[num_compromissos++] = (compromisso){alunos[2], {16, 0}, {22, 2, 2025}, "Aula de reforço"};
        compromissos[num_compromissos++] = (compromisso){alunos[0], {9, 30}, {23, 2, 2025}, "Reunião de grupo"};
        compromissos[num_compromissos++] = (compromisso){alunos[1], {11, 15}, {24, 2, 2025}, "Apresentação de projeto"};
        compromissos[num_compromissos++] = (compromisso){alunos[2], {13, 45}, {25, 2, 2025}, "Consulta com o orientador"};
        compromissos[num_compromissos++] = (compromisso){alunos[0], {15, 0}, {26, 2, 2025}, "Estudo em casa"};
        
        disciplina *disciplinas = alocar_disciplinas(tamanho_disciplinas);
        disciplinas[num_disciplinas++] = (disciplina){101, "Matemática"};
        disciplinas[num_disciplinas++] = (disciplina){102, "Física"};
        disciplinas[num_disciplinas++] = (disciplina){103, "Química"};
        disciplinas[num_disciplinas++] = (disciplina){104, "Biologia"};
        disciplinas[num_disciplinas++] = (disciplina){105, "História"};
        disciplinas[num_disciplinas++] = (disciplina){106, "Geografia"};
        disciplinas[num_disciplinas++] = (disciplina){107, "Literatura"};
        disciplinas[num_disciplinas++] = (disciplina){108, "Educação Física"};
        disciplinas[num_disciplinas++] = (disciplina){109, "Filosofia"};
        disciplinas[num_disciplinas++] = (disciplina){110, "Sociologia"};
        disciplinas[num_disciplinas++] = (disciplina){111, "Artes"};
        disciplinas[num_disciplinas++] = (disciplina){112, "Inglês"};
        disciplinas[num_disciplinas++] = (disciplina){113, "Espanhol"};
        disciplinas[num_disciplinas++] = (disciplina){114, "Programação"};
        disciplinas[num_disciplinas++] = (disciplina){115, "Economia"};
    
    int decisao=0;
    do
    {
    exibir_menu();
    scanf("%d",&decisao);
        switch(decisao)
    {
        case 1:
            cadastra_disciplina(&disciplinas, &num_disciplinas, &tamanho_disciplinas);
            break;
        case 2:
            cadastra_aluno(&alunos, &num_alunos, &tamanho_alunos, disciplinas);
            break;
        case 3:
                cadastra_compromisso(&compromissos, &num_compromissos, &tamanho_compromissos, alunos, num_alunos);
            break;
        case 4:
            char sub_escolha;
                do 
                {
                    exibir_submenu_compromissos();
                    scanf(" %c", &sub_escolha);
        
                    switch (sub_escolha) {
                        case 'a':
                            int RAa;
                            printf("Escolha o RA a ser consultado: ");
                            scanf(" %d", &RAa);
                            printf("\nImprimindo compromissos de um aluno...\n");
                            imprime_compromissos_aluno(compromissos, num_compromissos, RAa);
                            break;
                        case 'b':
                            printf("\nImprimindo compromissos de todos os alunos...\n");
                            imprime_todos_compromissos(compromissos, num_compromissos);
                            break;
                        case 'c':
                            data datac;
                            printf("Escolha a data a ser consultada: ");
                            while((scanf("%d/%d/%d",&datac.dia, &datac.mes, &datac.ano))!=3 || !verifica_data(&datac))
                            {
                                printf("Data inválida! Digite novamente no formato DD/MM/YYYY: ");
                            }
                            printf("\nImprimindo compromissos de uma data...\n");
                            imprime_compromissos_por_data(compromissos, num_compromissos, datac);
                            break;
                        case 'd':
                            printf("\nImprimindo compromissos de todas as datas...\n");
                            imprime_todos_compromissos_d(compromissos, num_compromissos);
                            break;
                        case 'e':
                            printf("\nVoltando ao menu principal...\n");
                            break;
                        default:
                            printf("\nOpcao invalida! Tente novamente.\n");
                    }
                } while (sub_escolha != 'e');
                break;
        case 5:
            int ra5;
            printf("Escolha o RA para extrair os dados: ");
            scanf("%d", &ra5);
            printf("\nImprimindo dados de um aluno...\n");
            imprime_dados_aluno(alunos, num_alunos, ra5);
            break;
        case 6:
            printf("\nImprimindo dados de todos os alunos...\n");
            imprime_dados_todos_alunos(alunos, num_alunos);
            break;
        case 7:
            return 0;
        default:
            printf("Número não representa uma ação.\n");
            break;
    }
    } while(decisao!=7);

	
    free(alunos);
    free(compromissos);
    free(disciplinas);
    return 0;
}
