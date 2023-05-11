#include <stdio.h>
#include <stdlib.h>
#include "libpilha.h"

/* 
 * Cria e retorna uma nova pilha.
 * Retorna NULL em caso de erro de alocação.
*/
pilha_t *pilha_cria () {
    pilha_t *p1;

    p1 = malloc(sizeof(pilha_t));
    p1->topo = NULL;
    p1->tamanho = 0;

    return p1;
}

/* Desaloca toda memoria da pilha e faz pilha receber NULL. */
void pilha_destroi (pilha_t **pilha) {

}
 
// Insere dado na pilha (politica LIFO).
// Retorna 1 em caso de sucesso e 0 em caso de falha.
int push (pilha_t *pilha, int dado) {

}

// Remove o topo (politica LIFO) e retorna o elemento no parametro dado.
// A funcao retorna 1 em caso de sucesso e 0 no caso da pilha estar vazia.

// VERIFICAR SE A PILHA NÃO ESTÁ VAZIA, CASO CONTRÁRIO PODE DAR UNDERFLOW
int pop (pilha_t *pilha, int *dado) {

}
 
/* Similar ao pop, mas retorna o elemento dado sem remove-lo. */
int pilha_topo (pilha_t *pilha, int *dado) {
    if (pilha->topo->dado != NULL)
        return pilha->topo->dado;
    return 0;
}

/* Retorna o numero de elementos da pilha, que pode ser 0. */
int pilha_tamanho (pilha_t *pilha) {
// pilha vazia
    if (pilha->topo->dado != NULL)
        return pilha->tamanho;
    return 0;
}

/* Retorna 1 se pilha vazia, 0 em caso contrario. */ 
int pilha_vazia (pilha_t *pilha) {

}