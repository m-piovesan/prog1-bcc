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

    /* ESCOLHER FUNCIONÁRIO ALEATÓRIO DE 1 A 100 */
    int aleat = rand() % 31;

    if (funcionarios == NULL || tarefas == NULL)
        return 1;

    for (int i = 0; i < 100; i++) {

        /* ACHAR UM LÍDER (30 < valor.liderança < 70) */
        while ((funcionarios[aleat].lideranca > 29) && (funcionarios[aleat].lideranca < 71))
            aleat = rand() % 31;

        /* GERA DIA ALEATÓRIO E CRIA COMPROMISSO */
        int diaReuniao = rand() % (31) + 1;
        compromisso_t *novoCompr = cria_compromisso(gera_horario(), gera_id(), "Reuniao");
        
        hc_compr(novoCompr); // usar essa função pra pegar as horas de início e minutos e tals

        "REUNIR L %.2d %.2d/%.2d %.2d:%.2d %.2d:%.2d T %.2d", aleat, i, /* mes_atual */,  

        - os valores são o LIDER, DIA, mes_atual, ini_h, ini_m, fim_h, fim_m, tarefa 

        /* SE A AGENDA DO LÍDER ESTIVER DISPONÍVEL, MARCA E PROCURA 2-6 FUNCIONÁRIOS PRA MESMA TAREFA */
        if (marca_compromisso_agenda(funcionarios[aleat].agenda, diaReuniao, novoCompr)) {
            int marcaDisponibilidade = 0;
            
            for (int j = 0; j < (rand() % 5) + 2; j++) {
                int aleat2 = rand() % 31;
                if ((funcionarios[aleat2].experiencia + (rand() % 31) - 20) < funcionarios[aleat].lideranca) {
                    if (marca_compromisso_agenda(funcionarios[aleat2].agenda, diaReuniao, novoCompr /* ver isso aqui hein, não sei que compromisso tem que passar nesse parâmetro */))
                        marcaDisponibilidade++;   
                }
            }
            
            /* SE NENHUM FUNCIONÁRIO PUDER PARTICIPAR, DESMARCA A REUNIÃO */
            if(!marcaDisponibilidade)
                desmarca_compromisso_agenda(funcionarios[aleat].agenda, diaReuniao, novoCompr);
            else 


        } else 
            printf("\tLIDER INDISPONIVEL \n");

        // prox_mes_agenda(); qual agenda passar no parâmetro?
    }

    prim_mes_agenda(/* sei lá zé */);

    for (int i = 1; i < 32; i++) {
        int t = 0;

        if (tarefas[t].tempo_conclusao > 0) {
            tarefas[t].tempo_conclusao -= min_trab * (funcionarios[/* não sei qual */].experiencia / 100.0) * ((100 - tarefas[t].dificuldade) / 100.0);
        }
    }

    return 0;
}