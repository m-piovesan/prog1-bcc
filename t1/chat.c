#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libagenda.h"

typedef struct {
    int lideranca;
    int experiencia;
    compromisso_t* agenda;
} funcionario_t;

typedef struct {
    int tempo_conclusao;
    int dificuldade;
} tarefa_t;

funcionario_t funcionarios[FUNCIONARIOS];

tarefa_t tarefas[TAREFAS];


int aleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

void inicializar_funcionarios(funcionario_t funcionarios[]) {
    for (int i = 0; i < FUNCIONARIOS; i++) {
        funcionarios[i].lideranca = aleatorio(0, 100);
        funcionarios[i].experiencia = aleatorio(20, 100);
        inicializar_agenda(&(funcionarios[i].agenda));
    }
}

void inicializar_tarefas(tarefa_t tarefas[]) {
    for (int i = 0; i < TAREFAS; i++) {
        tarefas[i].tempo_conclusao = aleatorio(600, 800);
        tarefas[i].dificuldade = aleatorio(30, 80);
    }
}

void marcar_reunioes(funcionario_t funcionarios[], tarefa_t tarefas[]) {
    for (int mes = 1; mes <= MESES; mes++) {
        for (int i = 0; i < TAREFAS; i++) {
            int lider = -1;

            do {
                lider = aleatorio(0, FUNCIONARIOS - 1);
            } while (funcionarios[lider].lideranca < 30 || funcionarios[lider].lideranca > 70);

            int ini_h = aleatorio(8, 12);
            int ini_m = aleatorio(0, 45) / 15 * 15;
            int fim_h = ini_h + aleatorio(1, 4);
            int fim_m = ini_m;

            int dia = aleatorio(1, 31);
            int tarefa_id = aleatorio(0, TAREFAS - 1);
            char descricao[100];

            snprintf(descricao, sizeof(descricao), "REUNIR L %.2d %.2d/%.2d %.2d:%.2d %.2d:%.2d T %.2d",
                lider, dia, mes, ini_h, ini_m, fim_h, fim_m, tarefa_id);

            compromisso_t compromisso;
            compromisso.id = tarefa_id;
            compromisso.ini_h = ini_h;
            compromisso.ini_m = ini_m;
            compromisso.fim_h = fim_h;
            compromisso.fim_m = fim_m;
            compromisso.dia = dia;
            compromisso.descricao = descricao;

            int membros[6];
            int qtd_membros = 0;

            for (int j = 0; j < FUNCIONARIOS; j++) {
                if (j != lider && funcionarios[lider].lideranca > funcionarios[j].lideranca + aleatorio(-20, 10)) {
                    membros[qtd_membros++] = j;
                }
            }

            if (qtd_membros > 0) {
                for (int j = 0; j < qtd_membros; j++) {
                    if (!marcar_compromisso(&(funcionarios[membros[j]].agenda), &compromisso)) {
                        qtd_membros = 0;
                        break;
                    }
                }
            }

            if (qtd_membros == 0) {
                remover_compromisso(&(funcionarios[lider].agenda), &compromisso);
            }
        }
    }
}

void realizar_reunioes(funcionario_t funcionarios[], tarefa_t tarefas[]) {
    for (int dia = 1; dia <= 31; dia++) {
        for (int i = 0; i < FUNCIONARIOS; i++) {
            dia_t *dia_atual = funcionarios[i].agenda.ptr_mes_atual->dias[dia - 1];
            compromisso_t *compromisso = dia_atual->comprs;

            while (compromisso != NULL) {
                tarefa_t *tarefa = &tarefas[compromisso->id];

                if (tarefa->tempo_conclusao > 0) {
                    int min_trab = (compromisso->fim_h - compromisso->ini_h) * 60 +
                        (compromisso->fim_m - compromisso->ini_m);

                    tarefa->tempo_conclusao -= min_trab * (funcionarios[i].experiencia / 100.0) *
                        ((100 - tarefa->dificuldade) / 100.0);

                    if (tarefa->tempo_conclusao <= 0) {
                        tarefa->tempo_conclusao = 0;
                        funcionarios[i].experiencia = (funcionarios[i].experiencia < 100) ?
                            funcionarios[i].experiencia + 1 : 100;
                    }

                    printf("%.2d/%.2d F %.2d: %s\n", dia, funcionarios[i].agenda.mes_atual,
                        i, compromisso->descricao);

                    if (tarefa->tempo_conclusao <= 0) {
                        printf("CONCLUÍDA\n");
                    } else {
                        printf("\tT %.2d D %.2d TCR %.2d\n", compromisso->id,
                            tarefa->dificuldade, tarefa->tempo_conclusao);
                    }
                }

                compromisso = compromisso->prox;
            }
        }
    }
}

int main() {
    srand(time(NULL));

    funcionario_t funcionarios[FUNCIONARIOS];
    tarefa_t tarefas[TAREFAS];

    inicializar_funcionarios(funcionarios);
    inicializar_tarefas(tarefas);

    marcar_reunioes(funcionarios, tarefas);
    realizar_reunioes(funcionarios, tarefas);

    return 0;
}
