// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} data;

typedef struct {
    int hora;
    int min;
} hora;

int verifica_hora(hora *h) {
    if (h->hora > 23 || h->hora < 0 || h->min > 59 || h->min < 0) 
    {
        return 0;
    }
    return 1;
}

int verifica_data(data *d) {
    if (d->mes < 1 || d->mes > 12) 
    {
        return 0;
    }

    int dias_no_mes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (d->ano % 4 == 0) 
    {
        dias_no_mes[2] = 29;
    }

    if (d->dia < 1 || d->dia > dias_no_mes[d->mes]) 
    {
        return 0;
    }

    return 1;
}

int main() {
    data data1={1,2,2020};
    printf("%02d/%02d/%04d\n",data1.dia,data1.mes,data1.ano);
    if(verifica_data(&data1))
    {
        printf("A data acima está correta.\n");
    } else {
        printf("A data acima está errada.\n");
    }
    
    data data2={29,2,2023};
    printf("%02d/%02d/%04d\n",data2.dia,data2.mes,data2.ano);
    if(verifica_data(&data2))
    {
        printf("A data acima está correta.\n");
    } else {
        printf("A data acima está errada.\n");
    }
    printf("\n\n");
    hora hora1={12,24};
    printf("%02d:%02d\n",hora1.hora,hora1.min);
    if(verifica_hora(&hora1))
    {
        printf("A hora acima está correta.\n");
    } else {
        printf("A hora acima está errada.\n");
    }
    hora hora2={24,68};
    printf("%02d:%02d\n",hora2.hora,hora2.min);
    if(verifica_hora(&hora2))
    {
        printf("A hora acima está correta.\n");
    } else {
        printf("A hora acima está errada.\n");
    }
    return 0;
}
