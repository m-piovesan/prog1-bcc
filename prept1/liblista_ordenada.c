#include "liblista_ordenada.h"
#include <stdlib.h>
#include <stdio.h>

/* 
 * Cria uma Lista vazia 
*/
lista_t *lista_cria () {
    lista_t *nova_lista = malloc(sizeof(lista_t));

    if (nova_lista == NULL)
        return NULL;

    nova_lista->ini = NULL;

    return nova_lista;
}

/* 
 * Destroi a Lista e a aponta para NULL
*/ 
void lista_destroi(lista_t **l) {
    if (l == NULL || *l == NULL)
        return;

    nodo_t *atual = (*l)->ini;

    while (atual != NULL) {
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
    novo->elemento = elemento;

    if (novo == NULL)
        return 0;

    if (l->ini == NULL) {
        l->ini = novo;
        novo->prox = NULL;
        return 1;
    }

    nodo_t *aux = l->ini;

    /* CASO A FILA TENHA SÓ UM NODO */
    if ((aux->prox == NULL) || (novo->elemento->chave <= aux->elemento->chave)) {
        if (elemento->chave <= aux->elemento->chave) {
            novo->prox = aux;
            l->ini = novo;
            return 1;
        }
        aux->prox = novo;
        novo->prox = NULL;
        return 1;
    }

    /* CASO TENHA MAIS DE UM */
    while (aux->prox != NULL && novo->elemento->chave > aux->prox->elemento->chave) {
        aux = aux->prox;
    }

    novo->prox = aux->prox;
    aux->prox = novo;
    return 1;
}


/* 
 * Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista.
*/

/* VER SE FUNCIONA PARA LISTAS DE TAMANHO PEQUENO (1/2) */
int lista_remove_ordenado(lista_t *l, elemento_t *elemento) {
    if (lista_vazia(l))
        return 0;

    nodo_t *aux = l->ini;

    /* Verifica se o elemento a ser removido é o primeiro da lista */
    if (elemento->chave == aux->elemento->chave) {
        l->ini = aux->prox;
        
        free(aux);
        return 1;
    }
    
    /* Percorre a lista até encontrar o elemento a ser removido */
    while (aux->prox != NULL && elemento->chave > aux->prox->elemento->chave) {
        aux = aux->prox;
    }
    
    /* Verifica se o elemento foi encontrado e realiza a remoção */
    if (aux->prox != NULL && elemento->chave == aux->prox->elemento->chave) {
        nodo_t *temp = aux->prox;
        aux->prox = temp->prox;
        
        free(temp);
        return 1;
    }

    /* Elemento não encontrado na lista */
    return 0;
}


int lista_vazia(lista_t *l) {
    if (l == NULL)
        return 1;
    return 0;
}