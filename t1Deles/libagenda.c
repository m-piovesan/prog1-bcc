#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libagenda.h"

/*
    Cria uma agenda vazia:
    O mes_atual deve ser inicializado com 1; 
    ptr_mes_atual deve ser definido. 
*/
agenda_t *cria_agenda() {
    agenda_t *novaAg = malloc(sizeof(agenda_t));

    if(novaAg == NULL)
        return NULL;
    
    novaAg->mes_atual = 1;
    novaAg->ptr_mes_atual = malloc(sizeof(mes_t));

    if (novaAg->ptr_mes_atual == NULL) {
        free(novaAg);
        return NULL;
    }

    novaAg->ptr_mes_atual->mes = 1;
    novaAg->ptr_mes_atual->dias = NULL;   
    novaAg->ptr_mes_atual->ant = novaAg->ptr_mes_atual;
    novaAg->ptr_mes_atual->prox = novaAg->ptr_mes_atual;

    return novaAg;
}

/*
   Cria um compromisso:
   Retorna um compromisso com as informacoes de data de hc, um identificador
   id e uma string de descricao. A funcao deve alocar um novo espaco de 
   armazenamento para receber a string descricao. 
*/ 
/* [X] VOCÊ TÁ FUNCIONANDO */
compromisso_t* cria_compromisso(horario_compromisso_t hc, int id, char* descricao) {
    compromisso_t* novoCompr = malloc(sizeof(compromisso_t));
    
    if (novoCompr == NULL) {
        destroi_compromisso(novoCompr);
        return NULL;
    }
        
    novoCompr->descricao = malloc(strlen(descricao) + 1); /* +1 para o caractere nulo de terminação */
    
    if (novoCompr->descricao == NULL) {
        destroi_descricao_compromisso(novoCompr);
        destroi_compromisso(novoCompr); 
        return NULL; 
    }

    strcpy(novoCompr->descricao, descricao); /* Copiar a string de descrição */
    
    novoCompr->id = id;
    novoCompr->inicio = (hc.ini_h * 60) + hc.ini_m;
    novoCompr->fim = (hc.fim_h * 60) + hc.fim_m;
    novoCompr->prox = NULL;

    return novoCompr;
}

/* destroi a descricao de um compromisso */
void destroi_descricao_compromisso(compromisso_t* compr) {
    free(compr->descricao);
    compr->descricao = NULL;
}

/* destroi um compromisso */
void destroi_compromisso(compromisso_t* compr) {
    destroi_descricao_compromisso(compr);
    free(compr);
    compr = NULL;
}

/* Libera toda memoria associado a agenda. */
void destroi_agenda(agenda_t* agenda) {
    if (agenda == NULL)
        return;

    mes_t* atual = agenda->ptr_mes_atual;

    if (atual == NULL)
        return;

    mes_t* prox = atual->prox;

    while (prox != agenda->ptr_mes_atual) {
        /* Libera os compromissos do mês atual */ 
        dia_t* dia = atual->dias;
        while (dia != NULL) {
            compromisso_t* compr = dia->comprs;
            while (compr != NULL) {
                compromisso_t* proxCompr = compr->prox;
                destroi_compromisso(compr);
                compr = proxCompr;
            }
            dia_t* proxDia = dia->prox;
            free(dia);
            dia = proxDia;
        }

        mes_t* proxAtual = prox;
        prox = prox->prox;
        free(atual);
        atual = proxAtual;
    }

    /* Libera os compromissos do último mês */ 
    dia_t* dia = atual->dias;
    while (dia != NULL) {
        compromisso_t* compr = dia->comprs;
        while (compr != NULL) {
            compromisso_t* proxCompr = compr->prox;
            free(compr->descricao);
            free(compr);
            compr = proxCompr;
        }
        dia_t* proxDia = dia->prox;
        free(dia);
        dia = proxDia;
    }

    free(atual);
    agenda->ptr_mes_atual = NULL;
    agenda->mes_atual = 0;
    free(agenda);
}

/* TESTA INTERSECÇÃO DE HORÁRIOS PARA MARCAR UM NOVO COMPROMISSO NA AGENDA
    RETORNA 1 EM CASO DE SUCESSO, 0 EM CASO DE ERRO E -1 EM CASO DE INTERSECÇÃO */
/* [X] VOCÊ TÁ FUNCIONANDO */
int testa_intersec(dia_t *listaDias, compromisso_t *novoCompr) {
    if (listaDias == NULL) 
        return 0;
    
    /* NOVO TERMINA ANTES DO PRIMEIRO COMEÇAR */
    if (novoCompr->fim < listaDias->comprs->inicio) {
        novoCompr->prox = listaDias->comprs;
        listaDias->comprs = novoCompr;
        // printf("--compromisso %d é o novo primeiro da lista\n\n", novoCompr->id);
        return 1;
    }

    compromisso_t *atual = listaDias->comprs;

    while ((atual->prox != NULL) && (novoCompr->inicio > atual->prox->fim)) 
        atual = atual->prox;
    
    /* ÚLTIMO DA LISTA */
    if (atual->prox == NULL) {
        atual->prox = novoCompr;
        // printf("--compromisso %d é o novo último da lista\n\n", novoCompr->id);
        return 1;
    }

    /* DECORRER DA LISTA */
    if ((novoCompr->inicio > atual->fim) && (novoCompr->fim < atual->prox->inicio)) {
        novoCompr->prox = atual->prox;
        atual->prox = novoCompr;
        // printf("--compromisso %d é novo na lista\n\n", novoCompr->id);
        return 1;
    }

    /* CONFLITO DE HORÁRIO */
    // printf("--compromisso %d tem conflito de horário 3\n\n", novoCompr->id);
    return -1;
}

int procura_compr_remove(compromisso_t *compr, dia_t *listaDias) {
    compromisso_t *listaCompr = listaDias->comprs;

    if(listaCompr == NULL)
        return 0;
    
/* COMPROMISSO É O PRIMEIRO DA LISTA */
    if (compr->id == listaCompr->id) {
        listaDias->comprs = listaCompr->prox;  /* Atualiza o ponteiro na lista */
    
        free(listaCompr->descricao);
        listaCompr->descricao = NULL;
    
        free(listaCompr);
        listaCompr = NULL;
    
        return 1;
    }

    while ((listaCompr->prox != NULL) && (compr->id != listaCompr->prox->id)) 
        listaCompr = listaCompr->prox;
            
    /* COMPROMISSO É O ÚLTIMO COMPROMISSO DA LISTA */
    if (listaCompr->prox == NULL) {
        free(listaCompr->descricao);
        listaCompr->descricao = NULL;
        
        free(listaCompr);
        listaCompr = NULL;

        return 1;
    }

    /* COMPROMISSO NO DECORRER DA LISTA */
    if (compr->id == listaCompr->prox->id) {
        compromisso_t *remover = listaCompr->prox;
                
        listaCompr->prox = remover->prox;

        free(remover->descricao);
        remover->descricao = NULL;

        free(remover);
        remover = NULL;

        return 1;
    }

    /* COMPROMISSO NÃO ESTÁ NA LISTA */
    return 0;
}

/* [X] VOCÊ TÁ FUNCIONANDO */
int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {
/* MÊS VAZIO */
    if (agenda->ptr_mes_atual->dias == NULL) {
        dia_t *novoDia = malloc(sizeof(dia_t));

        if (novoDia == NULL)
            return 0;

        novoDia->dia = dia;
        novoDia->prox = NULL;
        novoDia->comprs = compr;

        agenda->ptr_mes_atual->dias = novoDia;

        // printf("mês vazio\n");
        return 1;
    }

    dia_t *aux = agenda->ptr_mes_atual->dias; // você tá errado de alguma forma

    /* COMPROMISSO MARCADO PARA O PRIMEIRO DIA DO MÊS */
    if (dia == aux->dia) {
        if (aux == NULL) 
            return 0;

        if(aux->comprs == NULL) {
            aux->comprs = compr;
            compr->prox = NULL;
        }

        /* NOVO TERMINA ANTES DO PRIMEIRO COMEÇAR */
        if (compr->fim < aux->comprs->inicio) {
            compr->prox = aux->comprs;
            aux->comprs = compr;
            // printf("--compromisso %d é o novo primeiro da lista\n\n", compr->id);
            return 1;
        }

        compromisso_t *atual = aux->comprs;

        while ((atual->prox != NULL) && (compr->inicio > atual->prox->fim)) 
            atual = atual->prox;

        /* ÚLTIMO DA LISTA */
        if (atual->prox == NULL) {
            atual->prox = compr;
            // printf("--compromisso %d é o novo último da lista\n\n", compr->id);
            return 1;
        }

        /* DECORRER DA LISTA */
        if ((compr->inicio > atual->fim) && (compr->fim < atual->prox->inicio)) {
            compr->prox = atual->prox;
            atual->prox = compr;
            // printf("--compromisso %d é novo na lista\n\n", compr->id);
            return 1;
        }

        /* CONFLITO DE HORÁRIO */
        // printf("--compromisso %d tem conflito de horário 3\n\n", compr->id);
        return -1;
    }


        /* MUDAR QUEM É A CABEÇA DA LISTA (novo dia menor que dia alocado) */
        if (dia < aux->dia) {
            dia_t *novoDia = malloc(sizeof(dia_t));

            if (novoDia == NULL)
                return 0;

            novoDia->prox = agenda->ptr_mes_atual->dias;
            novoDia->dia = dia;
            novoDia->comprs = compr;
            agenda->ptr_mes_atual->dias = novoDia;
            // printf("mudar cabeça\n");
            return 1;
        }

    /* CASO TENHA MAIS DE UM DIA ALOCADO NESSE MÊS */
    while (aux->prox != NULL && dia > aux->prox->dia)
        aux = aux->prox;

    /* DIA DO COMPROMISSO JÁ ALOCADO */
    if (aux->prox != NULL && aux->prox->dia == dia) {
        if (aux == NULL) 
            return 0;

        compromisso_t *atual = aux->comprs;

        if(atual == NULL) {
            return 0;
        }

        /* ÚLTIMO DA LISTA */
        if (atual->prox == NULL) {
            atual->prox = compr;
            // printf("--compromisso %d é o novo último da lista\n\n", compr->id);
            return 1;
        }

    
        /* NOVO TERMINA ANTES DO PRIMEIRO COMEÇAR */
        if (compr->fim < aux->comprs->inicio) {
            compr->prox = aux->comprs;
            aux->comprs = compr;
            // printf("--compromisso %d é o novo primeiro da lista\n\n", compr->id);
            return 1;
        }


        while ((atual->prox != NULL) && (compr->inicio > atual->prox->fim)) 
            atual = atual->prox;
        
        /* ÚLTIMO DA LISTA */
        if (atual->prox == NULL) {
            atual->prox = compr;
            // printf("--compromisso %d é o novo último da lista\n\n", compr->id);
            return 1;
        }

        /* DECORRER DA LISTA */
        if ((compr->inicio > atual->fim) && (compr->fim < atual->prox->inicio)) {
            compr->prox = atual->prox;
            atual->prox = compr;
            // printf("--compromisso %d é novo na lista\n\n", compr->id);
            return 1;
        }

        /* CONFLITO DE HORÁRIO */
        // printf("--compromisso %d tem conflito de horário 3\n\n", compr->id);
        return -1;
    }

    if (aux->prox == NULL) {
        dia_t *novoDia = malloc(sizeof(dia_t));

        if (novoDia == NULL)
            return 0;

        novoDia->dia = dia;
        novoDia->prox = aux->prox;
        novoDia->comprs = compr;

        aux->prox = novoDia;
    }
    

    // printf("depois\n");

    return 1;
}


/* Desmarca o compromisso compr da agenda:
   O parametro compr eh um ponteiro para um compromisso existente da agenda.
   valores de retorno possiveis:
    1: em caso de sucesso
    0: caso nao tenha encontrado o compr */
/* [X] VOCÊ TÁ FUNCIONANDO */
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

/* Imprime a agenda do mes atual (mes atual) */
/* [X] VOCÊ TÁ FUNCIONANDO */
void imprime_agenda_mes(agenda_t* agenda) {   
    if ((agenda->ptr_mes_atual == NULL) || (agenda->ptr_mes_atual->dias == NULL))
        return;

    dia_t *auxDias = agenda->ptr_mes_atual->dias;
    compromisso_t *auxCompr = auxDias->comprs;

    while(auxDias != NULL) {
        while (auxCompr != NULL) {
            printf("\nID: %d\n",auxCompr->id);
            printf("Dia: %d\n",auxDias->dia);
            printf("Início: %d:%d\n",auxCompr->inicio / 60,auxCompr->inicio % 60);
            printf("Fim: %d:%d\n",auxCompr->fim / 60, auxCompr->fim % 60);
            printf("Descrição: %s\n",auxCompr->descricao);

            auxCompr = auxCompr->prox;
        }
        
        auxDias = auxDias->prox;

        if(auxDias == NULL)
            break;

        auxCompr = auxDias->comprs;
    }

    return;
}

/* Retorna o mes atual da agenda. */
int mes_atual_agenda(agenda_t *agenda) {
    return agenda->mes_atual;
}

/* Ajusta o mes_atual para 1 e aponta prt_mes_atual para o mes 1 na Lista de meses  */
void prim_mes_agenda(agenda_t* agenda) {
    agenda->mes_atual = 1;

    while (agenda->ptr_mes_atual->mes != 1)
        agenda->ptr_mes_atual = agenda->ptr_mes_atual->ant;

    return;
}

/* Avanca a agenda para o proximo mes, incrementando mes_atual.
 * O ponteiro ptr_mes_atual deve ser atualizado para apontar para o novo mes_atual.
 * Se o novo mes_atual nao existir deve ser alocado. A funcao retorna o inteiro 
 * mes_atual em caso de sucesso ou 0 caso contrario.  */ 
int prox_mes_agenda(agenda_t* agenda) {
    mes_t *aux = agenda->ptr_mes_atual;

    if (aux == NULL)
        return 0;

    if (aux->mes == 12) {
        aux = aux->prox;
        agenda->ptr_mes_atual = aux;
        agenda->mes_atual = 1;
        return agenda->mes_atual;
    }

    if (aux->prox->mes == aux->mes + 1) {
        agenda->ptr_mes_atual = aux->prox;
        agenda->mes_atual++;
        return agenda->mes_atual;
    }

    mes_t *novoMes = malloc(sizeof(mes_t));

    if (novoMes == NULL)
        return 0;

    novoMes->mes = aux->mes + 1;
    novoMes->prox = aux->prox;
    novoMes->ant = aux;
    novoMes->dias = NULL;

    agenda->ptr_mes_atual->prox->ant = novoMes;
    agenda->ptr_mes_atual->prox = novoMes;
    agenda->ptr_mes_atual = agenda->ptr_mes_atual->prox;
    agenda->mes_atual++;

    return agenda->mes_atual; 
}

int ant_mes_agenda(agenda_t* agenda) {
    mes_t *aux = agenda->ptr_mes_atual;

    if (aux == NULL)
        return 0;

    if (aux->ant->mes >= aux->mes) {
        if (aux->mes == 1) {
            if(aux->prox->mes == 1 && aux->prox->prox->mes == 1) {
                mes_t *novoMes = malloc(sizeof(mes_t));

                if (novoMes == NULL)
                    return 0;
            
                novoMes->mes = 12;
                novoMes->ant = aux->ant;
                novoMes->prox = aux;

                aux->ant = novoMes;
                aux->prox = novoMes;
                agenda->ptr_mes_atual = novoMes;
                agenda->mes_atual = 12;

                return agenda->mes_atual;    
            }
                
            aux = aux->ant;
            agenda->ptr_mes_atual = aux;
            agenda->mes_atual = 12;
            return agenda->mes_atual;
        }
        
        mes_t *novoMes = malloc(sizeof(mes_t));

        if (novoMes == NULL)
            return 0;

        novoMes->mes = aux->mes - 1;
        novoMes->ant = aux->ant;
        novoMes->prox = aux;
        novoMes->dias = NULL;

        agenda->ptr_mes_atual->ant = novoMes;
        agenda->ptr_mes_atual = aux->ant;
        agenda->mes_atual--;

        return agenda->mes_atual;
    }

    agenda->ptr_mes_atual = aux->ant;
    agenda->mes_atual = aux->mes - 1;
    return agenda->mes_atual;       
}


/* Retorna um ponteiro para a lista ligada de compromissos de um dia do mes
   ou NULL se vazia. A lista de compromissos retornada pode ser percorrida
   usando-se a funcao prox_compr. */ 
compromisso_t* compr_agenda(agenda_t* agenda, int dia) {
    dia_t *procuraDia = agenda->ptr_mes_atual->dias;

    if (procuraDia == NULL)
        return NULL;

    while ((procuraDia->prox != NULL) && (procuraDia->dia < dia)) 
        procuraDia = procuraDia->prox;

    if (procuraDia->dia == dia)
        return procuraDia->comprs;

    return NULL;
}

/* Retorna o próximo compromisso da lista de compromissos compr */
/* [X] VOCÊ TÁ FUNCIONANDO */
compromisso_t* prox_compr(compromisso_t* compr) {
    if (compr == NULL)
        return NULL;

    return compr->prox;
}

/* As funcoes abaixo sao usadas para acessar os membros da struct compromisso
   obtidos com a funcao prox_compr. */
/* [X] VOCÊ TÁ FUNCIONANDO */
horario_compromisso_t hc_compr(compromisso_t* compr) {
    horario_compromisso_t horario;

    horario.ini_h = (compr->inicio / 60);
    horario.ini_m = (compr->inicio % 60);

    horario.fim_h = (compr->fim / 60);
    horario.fim_m = (compr->fim % 60);

    return horario;
}

int id_compr(compromisso_t* compr) {
    return compr->id;
}

char* descricao_compr(compromisso_t* compr) {
    return compr->descricao;
}