int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {
    dia_t *aux = agenda->ptr_mes_atual->dias;

    /* MÊS VAZIO */
    if (aux == NULL) {
        // printf("mês vazio\n");
        return 0;
    }

    if (aux->dia == dia) {
        printf("\ndia %d é o primeiro da lista\n", aux->dia);
        

        //compromisso_t *listaCompr = listaDias->comprs;

        if(aux->comprs == NULL)
            return 0;
        
    /* COMPROMISSO É O PRIMEIRO DA LISTA */
        if (compr->id == aux->comprs->id) {
            compromisso_t *remover = aux->comprs;

            aux->comprs = aux->comprs->prox; /* Atualiza o ponteiro na lista */
        
            free(remover->descricao);
            remover->descricao = NULL;
        
            free(remover);
            remover = NULL;
        
            return 1;
        }

        while ((aux->comprs->prox != NULL) && (compr->id != aux->comprs->prox->id)) 
            aux->comprs = aux->comprs->prox;
                
        /* COMPROMISSO É O ÚLTIMO COMPROMISSO DA LISTA */
        if (aux->comprs->prox == NULL) {
            free(aux->comprs->descricao);
            aux->comprs->descricao = NULL;
            
            free(aux->comprs);
            aux->comprs = NULL;

            return 1;
        }

        /* COMPROMISSO NO DECORRER DA LISTA */
        if (compr->id == aux->comprs->prox->id) {
            compromisso_t *remover = aux->comprs->prox;
                    
            aux->comprs->prox = remover->prox;

            free(remover->descricao);
            remover->descricao = NULL;

            free(remover);
            remover = NULL;

            return 1;
        }

        /* COMPROMISSO NÃO ESTÁ NA LISTA */
        return 0;




    }

    /* MÊS COM UM DIA MALLOCADO */
    if (aux->prox == NULL) {
        if (aux->dia == dia) 
            return procura_compr_remove(compr, aux);

        /* DIA NÃO CORRESPONDE AO DIA DO COMPROMISSO */
        return 0;
    }

    /* MÊS COM MAIS DE 1 DIA MALLOCADO */
    while ((aux->prox != NULL) && (dia < aux->prox->dia))
        aux = aux->prox;    

    /* DIA NÃO ESTÁ NA LISTA */
    if(aux->prox == NULL) 
        return 0;

    /* DIA DO COMPROMISSO ESTÁ NA LISTA */
    if (aux->prox->dia == dia) {
        if(aux->prox->comprs == NULL)
            return 0;



        /* COMPROMISSO É O PRIMEIRO DA LISTA */
        if (compr->id == aux->prox->comprs->id) {
            compromisso_t *remover = aux->comprs;

            aux->comprs = aux->comprs->prox; /* Atualiza o ponteiro na lista */
        
            free(remover->descricao);
            remover->descricao = NULL;
        
            free(remover);
            remover = NULL;
        
            return 1;
        }

        while ((aux->prox->comprs->prox != NULL) && (compr->id != aux->prox->comprs->prox->id)) 
            aux->prox->comprs = aux->prox->comprs->prox;
                
        /* COMPROMISSO É O ÚLTIMO COMPROMISSO DA LISTA */
        if (aux->prox->comprs->prox == NULL) {
            free(aux->prox->comprs->descricao);
            aux->prox->comprs->descricao = NULL;
            
            free(aux->prox->comprs);
            aux->prox->comprs = NULL;

            return 1;
        }

        /* COMPROMISSO NO DECORRER DA LISTA */
        if (compr->id == aux->prox->comprs->prox->id) {
            compromisso_t *remover = aux->prox->comprs->prox;
                    
            aux->prox->comprs->prox = remover->prox;

            free(remover->descricao);
            remover->descricao = NULL;

            free(remover);
            remover = NULL;

            return 1;
        }

    }
        
        
        /* COMPROMISSO NÃO ESTÁ NA LISTA */
        return 0;

    return 0;
}