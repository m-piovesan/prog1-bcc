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

funcionario_t *inicializa_funcionarios() {
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

tarefa_t *inicializa_tarefas() {
    tarefa_t *vetTarefas = malloc(sizeof(tarefa_t) * 100);

    if (vetTarefas == NULL)
        return NULL;

    for (int i = 0; i < 100; i++) {
        vetTarefas[i].tempo_conclusao = (rand() % (800 - 600 + 1)) + 600;
        vetTarefas[i].dificuldade = (rand() % (80 - 30 + 1)) + 30;
    }

    return vetTarefas;
}

horario_compromisso_t gera_horario() {
    horario_compromisso_t horario;

    horario.ini_h = (rand() % 5) + 8;
    horario.ini_m = (rand() % 4) * 15;
    horario.fim_h = horario.ini_h + (rand() % 3) + 1;
    horario.fim_m = horario.ini_m;

    return horario;
}

int gera_id() {
    return rand() % 100;
}

int main() {
    srand(time(NULL));

    funcionario_t *funcionarios = inicializa_funcionarios();
    tarefa_t *tarefas = inicializa_tarefas();
    compromisso_t *novoCompr = cria_compromisso(gera_horario(), gera_id, "Reuniao");

    int aleat;

    if (funcionarios == NULL || tarefas == NULL)
        return 1;

    for (int i = 0; i < 100; i++) {
        aleat = rand() % 101;

        if ((funcionarios[aleat].lideranca > 29) && (funcionarios[aleat].lideranca < 71)) {
            int diaReuniao = rand() % (31) + 1;
            if (marca_compromisso_agenda(funcionarios[aleat].agenda, diaReuniao, novoCompr)) {
                int marcaDisponibilidade = 0;

                for (int j = 0; j < (rand() % 5) + 2; j++) {
                    int aleat2 = rand() % 31;

                    if ((funcionarios[aleat2].experiencia + (rand() % 31) - 20) < funcionarios[aleat].lideranca) {
                        if (marca_compromisso_agenda(funcionarios[aleat2].agenda, diaReuniao, novoCompr /* ver isso aqui hein, não sei que compromisso tem que passar nesse parâmetro */)) {
                            marcaDisponibilidade++;
                        }
                    }
                }   
            }
        }
    }


    return 0;
}