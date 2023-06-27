#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libagenda.h"

typedef struct funcionario {
    int lideranca;
    int experiencia;
    compromisso_t* agenda;
} funcionario_t;

typedef struct tarefa {
    int tempo_conclusao;
    int dificuldade;
} tarefa_t;

funcionario_t *inicializa_funcionarios () {
    funcionario_t *vetFuncionarios = malloc(sizeof(funcionario_t) * 30);

    if (vetFuncionarios == NULL) 
        return NULL;

    for (int i = 0; i < 30; i++) {
        vetFuncionarios[i].lideranca = rand() % 101;
        vetFuncionarios[i].experiencia = (rand() % (100 - 20 + 1)) + 20;
        vetFuncionarios[i].agenda = cria_agenda();

        if (vetFuncionarios[i].agenda == NULL)
            return NULL;
    }

    return vetFuncionarios;
}

tarefa_t *inicializa_tarefas () {
    tarefa_t *vetTarefas = malloc(sizeof(tarefa_t) * 100);

    if (vetTarefas == NULL)
        return NULL;

    for (int i = 0; i < 100; i++) {
        vetTarefas[i].tempo_conclusao = (rand() % (800 - 600 + 1)) + 600;
        vetTarefas[i].dificuldade = (rand() % (80 - 30 + 1)) + 30;
    }

    return vetTarefas;
}

int main () {
    srand(time(NULL));

    funcionario_t *funcionarios = inicializa_funcionarios();
    tarefa_t *tarefas = inicializa_tarefas();
    agenda_t *agenda = cria_agenda();

    if (funcionarios == NULL || tarefas == NULL || agenda == NULL)
        return 1;

    for (int i = 0; i < 100; i++) {

    }


    return 0;
}