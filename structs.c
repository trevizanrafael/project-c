#include <stdio.h>
#include <stdlib.h>

// Structs para o projeto

typedef struct
{
	int dia;
	int mes;
	int ano;
} data;

typedef struct
{
	int hora;
	int min;
} hora;

typedef struct
{
	int codigo_dis;
	char disciplina[100];
	float notas[4];
	float media;
} disciplina;

typedef struct
{
	int ra;
	char nome[100];
	td_data matricula;
	td_disciplina disciplinas[4];
	char email[100];
} aluno;

typedef struct {
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} compromisso;
