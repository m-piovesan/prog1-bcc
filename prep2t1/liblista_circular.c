#include <stdlib.h>
#include <stdio.h>
#include "liblista_circular.h"

/* 
 * Cria uma Lista vazia 
*/
lista_t *lista_cria () {
    lista_t *novaLista = malloc(sizeof(lista_t));

    if (lista_vazia(novaLista))
        return NULL;

    novaLista->ini = NULL;

    return novaLista;
}

/* 
 * Destroi a Lista e a aponta para NULL
*/ 
void lista_destroi(lista_t **l) {
    if (l == NULL || *l == NULL)
        return;

    nodo_t *atual = (*l)->ini->prox;

    while (atual != NULL && atual != (*l)->ini) {
        nodo_t *aux = atual;
        atual = atual->prox;
        free(aux->elemento);
        free(aux);
    }

    free(*l);
    *l = NULL;
}

/* 
 * Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario.
*/
int lista_insere_ordenado(lista_t *l, elemento_t *elemento) {
    if (lista_vazia(l))
        return 0;

    nodo_t *novo = malloc(sizeof(nodo_t));
    if (novo == NULL)
        return 0;

    novo->elemento = elemento;
    novo->prev = NULL;
    novo->prox = NULL;

    /* CASO A FILA ESTIVER VAZIA */
    if (l->ini == NULL) {
        l->ini = novo;
        novo->prox = novo;
        novo->prev = novo;
        return 1;
    }

    nodo_t *aux = l->ini;

    /* CASO A FILA TENHA SÓ UM NODO */
    if (aux->prox == aux) {
        if (elemento->chave <= aux->elemento->chave)
            l->ini = novo;
        
        novo->prev = aux;
        novo->prox = aux;
            
        aux->prev = novo;
        aux->prox = novo;
        
        return 1;
    }

    /* CASO O NOVO ELEMENTO SEJA MENOR DO QUE O PRIMEIRO DA LISTA */
    if (elemento->chave < aux->elemento->chave) {
        novo->prox = aux;
        novo->prev = aux->prev;

        aux->prev->prox = novo;
        aux->prev = novo;

        l->ini = novo;

        return 1;
    }

    /* CASO TENHA MAIS DE UM */
    while (aux->prox != l->ini && novo->elemento->chave > aux->prox->elemento->chave) {
        aux = aux->prox;
    }

    novo->prox = aux->prox;
    novo->prev = aux;

    aux->prox = novo;

    if (novo->prox == l->ini) 
        l->ini->prev = novo;
    
    return 1;
}

/* 
 * Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista.
*/
int lista_remove_ordenado(lista_t *l, elemento_t *elemento) {
    if (lista_vazia(l))
        return 0;

    nodo_t *aux = l->ini;

    /* Verifica se o elemento a ser removido é o primeiro da lista */
    if (elemento->chave == aux->elemento->chave) {
        aux->prev->prox = aux->prox;
        aux->prox->prev = aux->prev;
        
        l->ini = aux->prox;
    
        free(aux);
        return 1;
    }
    
    /* Percorre a lista até encontrar o elemento a ser removido */
    while (aux->prox != l->ini && elemento->chave > aux->prox->elemento->chave) {
        aux = aux->prox;
    }
    
    /* Verifica se o elemento foi encontrado e realiza a remoção */
    if (aux->prox != l->ini && elemento->chave == aux->prox->elemento->chave) {
        aux->prox = aux->prox->prox;
        aux->prox->prev = aux;
        
        return 1;
    }

    /* Elemento não encontrado na lista */
    return 0;
}

/* Retorna 1 se a lista esta vazia e 0 caso contrario */
int lista_vazia (lista_t *l) {
    if (l == NULL)
        return 1;
    return 0;
}