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
    if ((pilha == NULL) || (*pilha == NULL)) 
        return;
    
    while ((*pilha)->topo != NULL) {
        nodo_t *remove = (*pilha)->topo;
        (*pilha)->topo = (*pilha)->topo->prox;
        free(remove);
    }
    
    free(*pilha);
    *pilha = NULL;
}


/*
Remove o topo (politica LIFO) e retorna o elemento no parametro dado.
A funcao retorna 1 em caso de sucesso e 0 no caso da pilha estar vazia.
VERIFICAR SE A PILHA NÃO ESTÁ VAZIA, CASO CONTRÁRIO PODE DAR UNDERFLOW
*/
int pop (pilha_t *pilha, int *dado) {
   if(!pilha_vazia(pilha)) {
       nodo_t *aux;
       aux = pilha->topo;
       *dado = aux->dado;

       pilha->topo = pilha->topo->prox;

       free(aux);
       aux = NULL;
       pilha->tamanho--;
       
       return 1;
   }

   return 0;
}


/*
Insere dado na pilha (politica LIFO).
Retorna 1 em caso de sucesso e 0 em caso de falha.
*/

/*
Explicação: o novoNodo->prox vai receber o topo da pilha (entrou mais alguém na fila)
            depois o topo da pilha vai apontar pro novoNodo, que por sua vez, virou o final (topo) da fila
*/
int push (pilha_t *pilha, int dado) {
    nodo_t *novoNodo;
    novoNodo = malloc(sizeof(nodo_t));
  
    if (novoNodo == NULL)
       return 0;
  
    novoNodo->dado = dado;
    novoNodo->prox = NULL;

    novoNodo->prox = pilha->topo;
    pilha->topo = novoNodo;
    pilha->tamanho++;

   return 1;
}

/* Similar ao pop, mas retorna o elemento dado sem remove-lo. */
int pilha_topo (pilha_t *pilha, int *dado) {
    if (!pilha_vazia(pilha)) {
       *dado = pilha->topo->dado;
       return 1;
    }
    return 0;
}


/* Retorna o numero de elementos da pilha, que pode ser 0. */
int pilha_tamanho (pilha_t *pilha) {
   if (!pilha_vazia(pilha))
       return pilha->tamanho;
   return 0;
}

/* Retorna 1 se pilha vazia, 0 em caso contrario. */ 
int pilha_vazia (pilha_t *pilha) {
    if (!(pilha->topo))
        return 1;
    return 0;  
}