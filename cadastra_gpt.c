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

void cadastra_compromisso(compromisso compromissos[], int *num_compromissos) {
    if (*num_compromissos >= 100) 
        { // supondo um limite de 100 compromissos
            printf("Limite de compromissos atingido!\n");
            return;
        }

    compromisso novo; //declaracao do array do novo compromisso
    
    printf("Digite o RA do aluno: ");
    scanf("%d", &novo.aluno.ra);

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
