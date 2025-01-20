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
