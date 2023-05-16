#include "libfila.h"
#include <stdlib.h>

// typedef struct nodo {
//     int dado;
//     struct nodo *prox;
// } nodo_t;

// typedef struct fila {
//     nodo_t *cabeca;
//     nodo_t *cauda;
//     int tamanho;
// } fila_t;

/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
fila_t *fila_cria () {
    struct fila *f1;
    f1 = malloc (sizeof(struct fila));

    if (f1 = NULL)
        return NULL;
        
    f1->cabeca = NULL;
    f1->cauda = NULL;
    f1->tamanho = 0;
    
    return f1;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (fila_t **fila) {

}

/* 
 * Insere dado no final da fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (fila_t *fila, int dado) {
    nodo_t *novoDado;
    novoDado = malloc(sizeof(nodo_t));
    
    novoDado->dado = dado;
    novoDado->prox = NULL;

    fila->cauda = &novoDado;
    fila->tamanho++;
}

/* 
 * Remove o elemento do inicio da fila (politica FIFO) e o retorna
 * no parametro dado. Nao confundir com o retorno da funcao.
 * A funcao retorna 1 em caso de sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (fila_t *fila, int *dado) {

}

/* Retorna o numero de elementos da fila, que pode ser 0. */
int fila_tamanho (fila_t *fila) {
    if (fila!=NULL) 
        return fila->tamanho;    
    return -1;
}

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (fila_t *fila) {
    if ((fila->cabeca != NULL) && (fila->cauda != NULL))
        return 0;
    return 1;
}