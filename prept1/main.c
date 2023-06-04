#include <stdio.h>
#include <stdlib.h>
#include "liblista_ordenada.h"

int main() {
    // Criação da lista
    lista_t *lista = lista_cria();

    // Verificação se a lista foi criada com sucesso
    if (lista == NULL) {
        printf("Erro ao criar a lista!\n");
        return 1;
    }

    // Inserção de elementos ordenados na lista
    elemento_t *elem1 = malloc(sizeof(elemento_t));
    elem1->chave = 10;
    lista_insere_ordenado(lista, elem1);

    printf("Lista ordenada:\n");
    nodo_t *atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");

    elemento_t *elem2 = malloc(sizeof(elemento_t));
    elem2->chave = 9;
    lista_insere_ordenado(lista, elem2);

    printf("Lista ordenada:\n");
    atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");

    elemento_t *elem3 = malloc(sizeof(elemento_t));
    elem3->chave = 1;
    lista_insere_ordenado(lista, elem3);

    printf("Lista ordenada:\n");
    atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");

    elemento_t *elem4 = malloc(sizeof(elemento_t));
    elem4->chave = 7;
    lista_insere_ordenado(lista, elem4);

    printf("Lista ordenada:\n");
    atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");

/*
    // Impressão da lista
    printf("Lista ordenada:\n");
    atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");
*/

    // Remoção de um elemento da lista
    lista_remove_ordenado(lista, elem2);

    // Impressão da lista após a remoção
    printf("Lista após remoção:\n");
    atual = lista->ini;
    while (atual != NULL) {
        printf("%d ", atual->elemento->chave);
        atual = atual->prox;
    }
    printf("\n");

    // Liberação da memória ocupada pela lista
    lista_destroi(&lista);

    return 0;
}