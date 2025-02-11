int capacidade_alunos = 1; // Capacidade inicial do vetor de alunos
    int capacidade_compromissos = 10; // Capacidade inicial do vetor de compromissos

    // Aloca dinamicamente os vetores
    aluno *alunos = alocar_alunos(capacidade_alunos);
    compromisso *compromissos = alocar_compromissos(capacidade_compromissos);

    // Cadastra disciplinas
    disciplina disciplinas[5];
    cadastra_disciplina(disciplinas, 5);

    // Cadastra alunos
    cadastra_aluno(alunos, capacidade_alunos, disciplinas);

    // Cadastra compromissos
    int num_compromissos = 0;
    cadastra_compromisso(compromissos, &num_compromissos, alunos, capacidade_alunos);

    // Realoca o vetor de alunos se necessário
    if (capacidade_alunos < 2) {
        capacidade_alunos = 2;
        alunos = realocar_alunos(alunos, capacidade_alunos, 2);
    }

    // Realoca o vetor de compromissos se necessário
    if (capacidade_compromissos < 20) {
        capacidade_compromissos = 20;
        compromissos = realocar_compromissos(compromissos, capacidade_compromissos, 20);
    }

    // Libera a memória alocada
    free(alunos);
    free(compromissos);
