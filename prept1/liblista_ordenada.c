#include "liblista_ordenada.h"
#include <stdlib.h>
#include <stdio.h>

/* 
 * Cria uma Lista vazia 
*/
lista_t *lista_cria () {
    lista_t *nova_lista = malloc(sizeof(lista_t));

    if (lista_vazia(nova_lista))
        return NULL;

    nova_lista->ini = NULL;

    return nova_lista;
}

/* 
 * Destroi a Lista e a aponta para NULL
*/ 
void lista_destroi (lista_t **l) {

}

/* 
 * Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario.
*/
int lista_insere_ordenado (lista_t *l, elemento_t *elemento) {

}

/* 
 * Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista.
*/
int lista_remove_ordenado (lista_t *l, elemento_t *elemento) {
    if(lista_vazia(l))
        return 0;

    nodo_t *aux = l->ini;

    if (elemento->chave == l->ini->elemento->chave) {
        l->ini = l->ini->prox;
        
        free(aux);
        aux = NULL;

        return 1;
    }
    
    while ((aux->prox->prox != NULL) && (elemento->chave < aux->elemento->chave)) {
        aux = aux->prox;
    }
    
    if (elemento->chave == aux->elemento->chave) {
        
    }

}

int lista_vazia(lista_t *l) {
    if (l == NULL)
        return 1;
    return 0;
}