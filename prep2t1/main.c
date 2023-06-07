#include <stdio.h>
#include <stdlib.h>
#include "liblista_circular.h"

void imprime_lista(lista_t *l) {
    if (lista_vazia(l))
        return;

    nodo_t *aux = l->ini;

    do {
        printf("%d ", aux->elemento->chave);
        aux = aux->prox;
    } while (aux != l->ini);

    free(aux);
    aux = NULL;
    
    printf("\n");
}


int main() {
    lista_t *lista = lista_cria();

    // Insere elementos na lista
    elemento_t *elem1 = malloc(sizeof(elemento_t));
    elemento_t *elem2 = malloc(sizeof(elemento_t));
    elemento_t *elem3 = malloc(sizeof(elemento_t));
    
    elem1->chave = 2;
    elem2->chave = 0;
    elem3->chave = 1;

    lista_insere_ordenado(lista, elem1);
    lista_insere_ordenado(lista, elem2);
    lista_insere_ordenado(lista, elem3);

    // Imprime a lista
    imprime_lista(lista);

    // Remove um elemento da lista
    int removido = lista_remove_ordenado(lista, elem2);

    if (removido)
        printf("Elemento removido com sucesso!\n");
    else
        printf("Elemento não encontrado na lista.\n");

    // Imprime a lista novamente
    imprime_lista(lista);

    // Destroi a lista
    lista_destroi(&lista);

    return 0;
}