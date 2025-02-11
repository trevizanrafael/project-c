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
    int decisao;
    aluno alunos[1];
    exibir_menu();
    scanf("%d",&decisao);
    switch(decisao)
    {
        case 7:
            return 0;
        case 1:
            printf("i");
        default:
            printf("Número não representa uma ação.");
    }
    
    return 0;
}
