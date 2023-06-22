#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libagenda.h"

/*
    Cria uma agenda vazia:
    O mes_atual deve ser inicializado com 1; 
    ptr_mes_atual deve ser definido. 
*/
agenda_t* cria_agenda() {
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

    return novaAg;
}

/*
   Cria um compromisso:
   Retorna um compromisso com as informacoes de data de hc, um identificador
   id e uma string de descricao. A funcao deve alocar um novo espaco de 
   armazenamento para receber a string descricao. 
*/ 
compromisso_t* cria_compromisso(horario_compromisso_t hc, int id, char* descricao) {
    compromisso_t* novoCompr = malloc(sizeof(compromisso_t));
    
    if (novoCompr == NULL)
        return NULL;

    novoCompr->descricao = malloc(strlen(descricao) + 1); /* +1 para o caractere nulo de terminação */
    
    if (novoCompr->descricao == NULL) {
        free(novoCompr); 
        return NULL; 
    }

    strcpy(novoCompr->descricao, descricao); /* Copiar a string de descrição */
    
    novoCompr->id = id;
    novoCompr->inicio = hc.ini_h;
    novoCompr->fim = hc.fim_h;
    novoCompr->prox = NULL;

    return novoCompr;
}

/* Libera toda memoria associado a agenda. */
void destroi_agenda(agenda_t* agenda) {
    mes_t *auxMes = agenda->ptr_mes_atual;
    mes_t *removerMes = auxMes;

    while (auxMes != NULL) {
        dia_t *auxDia = auxMes->dias;
        dia_t *removerDia = auxDia;

        while (auxDia != NULL) {
            compromisso_t *auxCompr = auxDia->comprs;
            compromisso_t *removerCompr = auxCompr;

            while (auxCompr != NULL) {
                auxCompr = auxCompr->prox;
                free(removerCompr->descricao);
                removerCompr->descricao = NULL;
                free(removerCompr);
                removerCompr = NULL;
                removerCompr = auxCompr;
            }

            auxDia = auxDia->prox;
            free(removerDia);
            removerDia = NULL;
            removerDia = auxDia;
        }

        auxMes = auxMes->prox;
        free(removerMes);
        removerMes = NULL;
        removerMes = auxMes;
    }

    free(agenda);
    agenda = NULL;

    return;
}

int testa_intersec(dia_t *listaDias, compromisso_t *novoCompr) {
    /* NOVO TERMINA ANTES DO PRIMEIRO COMEÇAR */
    if (novoCompr->fim < listaDias->comprs->inicio) {
        novoCompr->prox = listaDias->comprs;
        listaDias->comprs = novoCompr;
        return 1;
    }

    while ((novoCompr->inicio < listaDias->comprs->fim) && (listaDias->comprs->prox != NULL))
        listaDias->comprs = listaDias->comprs->prox;

    /* NOVO É O ÚLTIMO COMPROMISSO DO DIA*/
    if (listaDias->comprs->prox == NULL) {
        listaDias->comprs->prox = novoCompr;
        return 1;
    }

    /* ENCAIXA NOVO NA LISTA DE COMPROMISSOS */
    if (novoCompr->fim < listaDias->comprs->prox->inicio) {
        novoCompr->prox = listaDias->comprs->prox;
        listaDias->comprs->prox = novoCompr;
        return 1;
    }
        
    /* CONFLITO DE HORÁRIO */
    return -1;    
}

int procura_compr_remove(compromisso_t *compr, dia_t *listaDias) {
compromisso_t *listaCompr = listaDias->comprs;

/* COMPROMISSO É O PRIMEIRO DA LISTA */
    if (compr->id == listaCompr->id) {
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
                
        listaCompr->prox = listaCompr->prox->prox;

        free(remover->descricao);
        remover->descricao = NULL;

        free(remover);
        remover = NULL;

        return 1;
    }

    /* COMPROMISSO NÃO ESTÁ NA LISTA */
    return 0;
}

/* Marca um compromisso na agenda:
   valores de retorno possiveis:
    -1: compromisso tem interseccao com outro
     0: erro de alocacao de memoria
     1: sucesso

    A lista de compromisso eh ordenada pelo horario de inicio. Eh necessario
    testar a interseccao entre horarios de inicio e de fim no compromisso novo
    considerando o compromisso anterior e o proximo, caso existam. */
int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {
    dia_t *aux = agenda->ptr_mes_atual->dias;
    horario_compromisso_t horario = hc_compr(compr);
    compromisso_t *novoCompr = cria_compromisso(horario, compr->id, compr->descricao);

/* MÊS VAZIO */
    if (aux == NULL) {
        dia_t *novoDia = malloc(sizeof(dia_t));

        if (novoDia == NULL)
            return 0;

        novoDia->dia = dia;
        novoDia->prox = NULL;
        novoDia->comprs = novoCompr;

        aux = novoDia;
        printf("oi\n");
        return 1;
    }

/* 1 DIA MALLOCADO NO MÊS */
    if (aux->prox == NULL) {
        dia_t *novoDia = malloc(sizeof(dia_t));

        if (novoDia == NULL)
            return 0;

        /* MUDAR QUEM É A CABEÇA DA LISTA (novo dia menor que dia mallocado)*/
        if (dia < aux->dia) {
            novoDia->prox = aux;
            aux = novoDia;
            aux->dia = dia;
            aux->comprs = novoCompr;

            return 1;
        }
            
        /* COMPROMISSO MARCADO PRO ÚNICO DIA DO MÊS */
        if (dia == aux->dia)
            return testa_intersec(aux, novoCompr);

        /* COMPROMISSO MARCADO PRA ALGUM DIA DEPOIS DO ÚNICO MALLOCADO */
        novoDia->prox = NULL;
        novoDia->comprs = novoCompr;
        aux->prox = novoDia;

        return 1;
    }   

/* CASO TENHA MAIS DE UM DIA MALLOCADO NESSE MÊS */
    while ((aux->prox != NULL) && (dia < aux->prox->dia))
        aux = aux->prox;

    /* DIA DO COMPROMISSO JÁ MALLOCADO */
    if (aux->prox->dia == dia) 
        return testa_intersec(aux->prox, novoCompr);

    /* O DIA DO NOVO COMPROMISSO AINDA NÃO FOI MALLOCADO */
    dia_t *novoDia = malloc(sizeof(dia_t));

    if (novoDia == NULL)
        return 0;

    novoDia->dia = dia;
    novoDia->comprs = novoCompr;

    /* CASO O NOVO DIA SEJA O ÚLTIMO DA LISTA */
    if (aux->prox == NULL) {
        novoDia->prox = NULL;
        aux->prox = novoDia;
        return 1;
    }

    /* CASO ESTEJA NO DECORRER DA LISTA */
    novoDia->prox = aux->prox;
    aux->prox = novoDia;
    return 1;
}

/* Desmarca o compromisso compr da agenda:
   O parametro compr eh um ponteiro para um compromisso existente da agenda.
   valores de retorno possiveis:
    1: em caso de sucesso
    0: caso nao tenha encontrado o compr */
int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {
    dia_t *aux = agenda->ptr_mes_atual->dias;

    /* MÊS VAZIO */
    if (aux == NULL)
        return 0;

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

    /* DIA DO COMPROMISSO ESTÁ NA LISTA */
    if (aux->prox->dia == dia)
        return procura_compr_remove(compr, aux->prox);

    /* DIA NÃO ESTÁ NA LISTA */
    return 0;
}

/* Imprime a agenda do mes atual (mes atual) */
void imprime_agenda_mes(agenda_t* agenda) {   
    if (agenda->ptr_mes_atual == NULL)
        return;
    
    dia_t *auxDias = agenda->ptr_mes_atual->dias;
    compromisso_t *auxCompr = auxDias->comprs;

    while(auxDias != NULL) {
        while (auxCompr != NULL) {
            printf("ID: %d\n",auxCompr->id);
            printf("Início (horas): %d\n",auxCompr->inicio);
            printf("Fim (horas): %d\n",auxCompr->fim);
            printf("Descrição: %s\n",auxCompr->descricao);
            printf("\n");

            auxCompr = auxCompr->prox;
        }

        auxDias = auxDias->prox;
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

// CORRIGIR ESSA FUNÇÃO E A ANT_MES

int prox_mes_agenda(agenda_t* agenda) {
    mes_t *aux = agenda->ptr_mes_atual;

    if ((aux->prox->mes) == ((aux->mes) + 1)) {
        aux = aux->prox;
        agenda->mes_atual++;
        return agenda->mes_atual;
    }
    
    if (aux->mes == 12) {
        aux = aux->prox;
        agenda->mes_atual = 1;
        return agenda->mes_atual;
    }

    mes_t *novoMes = malloc(sizeof(mes_t));

    if (novoMes == NULL)
        return 0;

    novoMes->prox = aux->prox;
    novoMes->ant = aux;
    novoMes->mes = aux->mes + 1;

    aux->prox->ant = novoMes;
    aux->prox = novoMes;
    aux = aux->prox;
    
    agenda->mes_atual = aux->mes;

    return aux->mes;
}

/* Analogo ao prox_mes_agenda porem decrementa mes_atual. */ 
int ant_mes_agenda(agenda_t* agenda) {
    mes_t *aux = agenda->ptr_mes_atual;

   if ((aux->ant->mes) == ((aux->mes) - 1)) {
        aux = aux->ant;
        agenda->mes_atual--;
        return agenda->mes_atual;
    }
    
    if (aux->mes == 1) {
        aux = aux->ant;
        agenda->mes_atual = 12;
        return agenda->mes_atual;
    }

    mes_t *novoMes = malloc(sizeof(mes_t));

    if (novoMes == NULL)
        return 0;

    novoMes->mes = aux->mes - 1;
    novoMes->prox = aux;
    novoMes->ant = aux->ant;
    
    aux->ant->prox = novoMes;
    aux->ant = novoMes;
    aux = aux->ant;

    agenda->mes_atual = aux->mes;

    return aux->mes;
}

/* Retorna um ponteiro para a lista ligada de compromissos de um dia do mes
   ou NULL se vazia. A lista de compromissos retornada pode ser percorrida
   usando-se a funcao prox_compr. */ 
compromisso_t* compr_agenda(agenda_t* agenda, int dia) {
    dia_t *procuraDia = agenda->ptr_mes_atual->dias;

    if (procuraDia == NULL)
        return NULL;

    while (procuraDia->dia < dia) 
        procuraDia = procuraDia->prox;

    if (procuraDia->dia == dia)
        return procuraDia->comprs;

    return NULL;
}

/* Retorna o próximo compromisso da lista de compromissos compr */
compromisso_t* prox_compr(compromisso_t* compr) {
    if (compr == NULL)
        return NULL;

    return compr->prox;
}

/* As funcoes abaixo sao usadas para acessar os membros da struct compromisso
   obtidos com a funcao prox_compr. */
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

/*  Essa funcao nao eh extritamente necessaria, o objetivo é
    que o programa principal apresente os dados. 
    Porem pode ser util para voces durante o desenvolvimento 

void imprime_agenda_mes(agenda_t* agenda) {

}
*/