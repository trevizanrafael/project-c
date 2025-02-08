int verifica_compromissos_do_dia(compromisso compromissos[], int num_compromissos, int ra, data d, hora h) {
    int count = 0;

    for (int i = 0; i < num_compromissos; i++) {
        if (compromissos[i].aluno.ra == ra &&
            compromissos[i].data.dia == d.dia &&
            compromissos[i].data.mes == d.mes &&
            compromissos[i].data.ano == d.ano) {

            count++;

            // Regra b: verificar se o horário coincide com outro compromisso do mesmo dia
            if (compromissos[i].horario.hora == h.hora && compromissos[i].horario.min == h.min) {
                printf("Erro: O aluno já tem um compromisso nesse horário!\n");
                return -1;
            }
        }
    }

    // Regra a: se o aluno já tiver 2 compromissos no mesmo dia, não pode cadastrar mais
    if (count >= 2) {
        printf("Erro: O aluno já tem dois compromissos cadastrados nessa data!\n");
        return -1;
    }

    return 0; // Sem problemas, pode cadastrar
}

void cadastra_compromisso(compromisso compromissos[], int *num_compromissos) {
    if (*num_compromissos >= 100) { // Supondo um limite de 100 compromissos
        printf("Limite de compromissos atingido!\n");
        return;
    }

    compromisso novo;
    
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

    // Verifica se o aluno já tem dois compromissos nesse dia ou se o horário coincide
    if (verifica_compromissos_do_dia(compromissos, *num_compromissos, novo.aluno.ra, novo.data, novo.horario) == -1) {
        return; // Impede o cadastro do compromisso
    }

    printf("Digite a descrição do compromisso: ");
    scanf(" %[^\n]", novo.descricao);

    // Adiciona o compromisso ao array
    compromissos[*num_compromissos] = novo;
    (*num_compromissos)++;

    printf("Compromisso cadastrado com sucesso!\n");
}
