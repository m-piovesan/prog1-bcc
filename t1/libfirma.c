#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libagenda.h"
#define MAX_TAM_STRING 35
#define TOTAL_FUNCIONARIOS 30
#define TOTAL_TAREFAS 100

typedef struct funcionario {
    int lideranca;
    int experiencia;
    agenda_t* agenda;
} funcionario_t;

typedef struct tarefa {
    int tempo_conclusao;
    int dificuldade;
} tarefa_t;

funcionario_t *inicializa_funcionarios() {
    funcionario_t *vetFuncionarios = malloc(sizeof(funcionario_t) * TOTAL_FUNCIONARIOS);

    if (vetFuncionarios == NULL) 
        return NULL;

    for (int i = 0; i < TOTAL_FUNCIONARIOS; i++) {
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

compromisso_t *formata_compromisso (funcionario_t *funcionarios, int dia, int idFunc, int idTarefa) {
    compromisso_t *novoCompr;
    horario_compromisso_t horarioReuni = gera_horario();

    char descricao[MAX_TAM_STRING];
    sprintf(descricao, "REUNIR L %.2d %.2d/%.2d %.2d:%.2d %.2d:%.2d T %.2d", idFunc, dia, funcionarios[idFunc].agenda->mes_atual, horarioReuni.ini_h, horarioReuni.ini_m, horarioReuni.fim_h, horarioReuni.fim_m, idTarefa);

    novoCompr = cria_compromisso(horarioReuni, idTarefa, descricao);

    return novoCompr;
}

void zera_vetor(int vet[], int tam) {
    for(int i = 0; i < tam; i++) 
        vet[i] = 0;
}

int gera_id_tarefas(int vet[]) {
    int id = rand() % 100;

    while (vet[id])
        id = rand() % 100;

    vet[id] = 1;

    return id;
}

int main() {
    srand(time(NULL));

    funcionario_t *funcionarios = inicializa_funcionarios();
    tarefa_t *tarefas = inicializa_tarefas();
    int vetIdTarefa = malloc(sizeof(int) * TOTAL_TAREFAS);

    /* ESCOLHER FUNCIONÁRIO ALEATÓRIO DE 1 A 100 */
    int idLider = rand() % 31;

    if (funcionarios == NULL || tarefas == NULL)
            return 1;

    do {    
        /* LOOP PRA MARCAR AS 100 TAREFAS DO MÊS */
        for (int i = 0; i < TOTAL_TAREFAS; i++) {

            /* ACHAR UM LÍDER (30 < valorLiderança < 70) */
            while ((funcionarios[idLider].lideranca > 29) && (funcionarios[idLider].lideranca < 71))
                idLider = rand() % 31;

            /* GERA DIA E ID ALEATÓRIOS, DAÍ CRIA COMPROMISSO */
            int diaReuniao = rand() % (31) + 1;
            zera_vetor(vetIdTarefa, TOTAL_TAREFAS);
            compromisso_t *novoCompr = formata_compromisso(funcionarios, diaReuniao, idLider, gera_id_tarefas(vetIdTarefa));

            /* SE A AGENDA DO LÍDER ESTIVER DISPONÍVEL, PROCURA 2-6 FUNCIONÁRIOS PRA MESMA TAREFA */
            if (marca_compromisso_agenda(funcionarios[idLider].agenda, diaReuniao, novoCompr)) {
                int marcaDisponibilidade = 0;
                int nFuncionariosAleat = (rand() % 5) + 2;

                printf("%s\tMEMBROS: ",novoCompr->descricao);

                for (int j = 0; j < nFuncionariosAleat; j++) {
                    int funcAleat = rand() % 31;
                    
                    if ((funcionarios[funcAleat].experiencia + (rand() % 31) - 20) < funcionarios[idLider].lideranca) {
                        printf(" %.2d:",funcionarios[funcAleat]);
                        
                        if (marca_compromisso_agenda(funcionarios[funcAleat].agenda, diaReuniao, novoCompr)) {
                            marcaDisponibilidade++;
                            printf("OK");   
                        } else
                            printf("IN"); // dar um jeito de quantos todos for IN, imprimir só vazia
                    }
                }

                /* SE NENHUM FUNCIONÁRIO PUDER PARTICIPAR, DESMARCA A REUNIÃO */
                if(!marcaDisponibilidade) {
                    desmarca_compromisso_agenda(funcionarios[idLider].agenda, diaReuniao, novoCompr);
                    printf("VAZIA");
                }
            
            } else 
                printf("\tLIDER INDISPONIVEL \n");     
        }   
        
        for (int j = 0; j < 30; j++)
            prox_mes_agenda(funcionarios[j].agenda);
    } while (funcionarios[29].agenda->mes_atual != 1);  

    for (int i = 0; i < 30; i++)
        prim_mes_agenda(funcionarios[i].agenda);

    for (int i = 1; i < 32; i++) {
        int t = 0;

        if (tarefas[t].tempo_conclusao > 0) {
            tarefas[t].tempo_conclusao -= tarefas[i]. mintrab * (funcionarios[/* não sei qual */].experiencia / 100.0) * ((100 - tarefas[t].dificuldade) / 100.0);
        }
    }

    return 0;
}