// Online C compiler to run C program online
#include <stdio.h>

typedef struct {
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} compromisso;

void cadastra_compromisso(compromisso compromissos, int num_compromissos) {
    aluno alunos[num_compromissos];
    cadastra_aluno(alunos, num_compromissos);
    
}

int main() {
    
    return 0;
}
