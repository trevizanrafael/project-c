int verifica_data(data *d) {
    if((d->ano)%4==0)
    {
        if(d->mes == 1 || d->mes == 3 || d->mes == 5 || d->mes == 7 || d->mes == 8 || d->mes == 10 || d->mes == 12)
            {
                if(d->dia>31 || d->dia<1)
                {
                    return 0;
                } else {
                        return 1;
                    }
            } else if(d->mes == 4 || d->mes == 6 || d->mes == 9 || d->mes == 11)
                {
                    if(d->dia>30 || d->dia<1)
                    {
                        return 0;
                    } else {
                        return 1;
                    }
                } else if(d->mes==2)
                    {
                        if(d->dia>29 || d->dia<1)
                        {
                            return 0;
                        } else {
                            return 1;
                        }   
                    } else if (d->mes>12||d->mes<1)
                        {
                            return 0;
                        }
    } 
    else 
    {
        if(d->mes == 1 || d->mes == 3 || d->mes == 5 || d->mes == 7 || d->mes == 8 || d->mes == 10 || d->mes == 12)
            {
                if(d->dia>31 || d->dia<1)
                {
                    return 0;
                } else {
                        return 1;
                    }
            } else if(d->mes == 4 || d->mes == 6 || d->mes == 9 || d->mes == 11)
                {
                    if(d->dia>30 || d->dia<1)
                    {
                        return 0;
                    } else {
                        return 1;
                    }
                } else if(d->mes==2)
                    {
                        if(d->dia>28 || d->dia<1)
                        {
                            return 0;
                        } else {
                            return 1;
                        }   
                    } else if (d->mes>12||d->mes<1)
                        {
                            return 0;
                        }
    }
}
