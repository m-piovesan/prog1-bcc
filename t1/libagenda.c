#include <stdio.h>
#include <stdlib.h>
#include "libagenda.h"

/*
    Cria uma agenda vazia:
    O mes_atual deve ser inicializado com 1; 
    ptr_mes_atual deve ser definido. 
*/
agenda_t* cria_agenda() {
    agenda_t *novaAg; 
    novaAg = malloc(sizeof(agenda_t));

    if(novaAg == NULL)
        return NULL;
    
    novaAg->ptr_mes_atual = malloc(sizeof(mes_t));

    if (novaAg->ptr_mes_atual == NULL) {
        free(novaAg);
        return NULL;
    }
    
    novaAg->mes_atual = 1;

    return novaAg;
}

/*
   Cria um compromisso:
   Retorna um compromisso com as informacoes de data de hc, um identificador
   id e uma string de descricao. A funcao deve alocar um novo espaco de 
   armazenamento para receber a string descricao. 
*/ 
compromisso_t* cria_compromisso(horario_compromisso_t hc, int id, char* descricao, size_t tamanho_descricao) {
    compromisso_t* novoCompr = malloc(sizeof(compromisso_t));
    
    if (novoCompr == NULL) {
        return NULL;
    }

    novoCompr->descricao = malloc(tamanho_descricao + 1); // +1 para o caractere nulo de terminação
    
    if (novoCompr->descricao == NULL) {
        free(novoCompr); 
        return NULL; 
    }

    strcpy(novoCompr->descricao, descricao); // Copiar a string de descrição para o novo local alocado
    
    novoCompr->id = id;
    novoCompr->inicio = hc.ini_h;
    novoCompr->fim = hc.fim_h;
    novoCompr->prox = NULL;

    return novoCompr;
}

/* Libera toda memoria associado a agenda. */
void destroi_agenda(agenda_t* agenda) {

}

/* Marca um compromisso na agenda:
   valores de retorno possiveis:
    -1: compromisso tem interseccao com outro
     0: erro de alocacao de memoria
     1: sucesso

    A lista de compromisso eh ordenada pelo horario de inicio. Eh necessario
    testar a interseccao entre horarios de inicio e de fim no compromisso novo
    considerando o  compromisso anterior e o proximo, caso existam. */
int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {

}

/* Desmarca o compromisso compr da agenda:
   O parametro compr eh um ponteiro para um compromisso existente da agenda.
   valores de retorno possiveis:
    1: em caso de sucesso
    0: caso nao tenha encontrado o compr */
int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr) {

}

/* Imprime a agenda do mes atual (mes atual) */
void imprime_agenda_mes(agenda_t* agenda) {
    
}

/* Retorna o mes atual da agenda. */
int mes_atual_agenda(agenda_t *agenda) {
    return agenda->mes_atual;
}

/* Ajusta o mes_atual para 1 e aponta prt_mes_atual para o mes 1 na Lista de 
 * meses  */
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

}

/* Analogo ao prox_mes_agenda porem decrementa mes_atual. */ 
int ant_mes_agenda(agenda_t* agenda) {

}

/* Retorna um ponteiro para a lista ligada de compromissos de um dia do mes
   ou NULL se vazia. A lista de compromissos retornada pode ser percorrida
   usando-se a funcao prox_compr. */ 
compromisso_t* compr_agenda(agenda_t* agenda, int dia) {

}

/* Retorna o primeiro compromisso da lista de compromissos compr e avanca
 * para o prox. Retorna NULL se a lista esta vazia, ou seja, sem compromissos.*/
compromisso_t* prox_compr(compromisso_t* compr) {

}

/* As funcoes abaixo sao usadas para acessar os membros da struct compromisso
   obtidos com a funcao prox_compr. */
horario_compromisso_t hc_compr(compromisso_t* compr) {

}

int id_compr(compromisso_t* compr) {

}

char* descricao_compr(compromisso_t* compr) {

}

/*  Essa funcao nao eh extritamente necessaria, o objetivo é
    que o programa principal apresente os dados. 
    Porem pode ser util para voces durante o desenvolvimento 
*/ 
void imprime_agenda_mes(agenda_t* agenda) {

}