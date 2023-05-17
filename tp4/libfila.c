#include "libfila.h"
#include <stdlib.h>

/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
fila_t *fila_cria () {
    fila_t *f1;
    f1 = malloc (sizeof(fila_t));

    if (f1 == NULL)
        return NULL;

    f1->cabeca = NULL;
    f1->cauda = NULL;
    f1->tamanho = 0;
    
    return f1;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi(fila_t **fila) {
    if ((fila == NULL) || (*fila == NULL)) {
        return;
    }
    
    while ((*fila)->cabeca != NULL) {
        nodo_t *remove = (*fila)->cabeca;
        (*fila)->cabeca = (*fila)->cabeca->prox;
        free(remove);
    }
    
    free(*fila);
    *fila = NULL;
}

/* 
 * Insere dado no final da fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (fila_t *fila, int dado) {
    nodo_t *novoDado;
    novoDado = malloc(sizeof(nodo_t));

    if (novoDado == NULL)
        return 0;

    novoDado->dado = dado;
    novoDado->prox = NULL;

    if(fila_vazia(fila)) {
        fila->cabeca = novoDado;
        fila->cauda = novoDado;
    } else {
/*não entendi pq tanto o cauda quanto o cauda->prox recebem a mesma coisa*/
        fila->cauda->prox = novoDado;
        fila->cauda = novoDado;
    }

    fila->tamanho++;

    return 1;
}

/* 
 * Remove o elemento do inicio da fila (politica FIFO) e o retorna
 * no parametro dado. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (fila_t *fila, int *dado) {
    if(fila_vazia(fila))
        return 0;

    nodo_t *remove;
    remove = fila->cabeca;
    *dado = remove->dado;

    if (fila->cabeca == fila->cauda) {
        fila->cabeca = NULL;
        fila->cauda = NULL;
    } else {
        fila->cabeca = fila->cabeca->prox;
    }
    
    free(remove);
    fila->tamanho--;
    
    return 1;
}

/* Retorna o numero de elementos da fila, que pode ser 0. */
int fila_tamanho (fila_t *fila) {
/* possível erro aqui */
    if (fila!=NULL) 
        return fila->tamanho;    
    return -1;
}

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (fila_t *fila) {
    if (fila_tamanho(fila) == 0)
        return 1;
    return 0;
}