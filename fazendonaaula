#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "libagenda.h"

#define MAX_TAM_STRING 35
#define TOTAL_FUNCIONARIOS 30
#define TOTAL_TAREFAS 100
#define DIAS_MES 31
#define MESES_ANO 12

typedef struct funcionario {
    int lideranca;
    int experiencia;
    agenda_t* agenda;
} funcionario_t;

typedef struct tarefa {
    int tempo_conclusao;
    int dificuldade;
} tarefa_t;

void inicializa_funcionarios(funcionario_t *vetFuncionarios) {
    for (int i = 0; i < TOTAL_FUNCIONARIOS; i++) {
        vetFuncionarios[i].lideranca = rand() % 101;
        vetFuncionarios[i].experiencia = (rand() % (100 - 20 + 1)) + 20;
        vetFuncionarios[i].agenda = cria_agenda();
    }
}

void inicializa_tarefas(tarefa_t *vetTarefas) {
    for (int i = 0; i < 100; i++) { 
        vetTarefas[i].tempo_conclusao = (rand() % (800 - 600 + 1)) + 600;
        vetTarefas[i].dificuldade = (rand() % (80 - 30 + 1)) + 30;
    }
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

int gera_id_tarefas() {
    return aleat(0,99);
}


int main() {
    srand(time(NULL));

    funcionario_t funcionarios[TOTAL_FUNCIONARIOS];
    inicializa_funcionarios(funcionarios);

    tarefa_t tarefas[TOTAL_TAREFAS];
    inicializa_tarefas(tarefas);

    int vetIdTarefa[TOTAL_TAREFAS];

    do {
        for (int i = 0; i < TOTAL_TAREFAS; i++) {

            /* achar um líder */
            int idLider = aleat(0,29);
            while (!((funcionarios[idLider].experiencia >= 30) && (funcionarios[idLider].experiencia <= 70))) 
                idLider = aleat(0,29);
                
            /* GERA DIA E ID ALEATÓRIOS, DAÍ CRIA COMPROMISSO */
            int diaReuniao = aleat(1, DIAS_MES);
            int idTarefa = gera_id_tarefas();
            compromisso_t *novoCompr = formata_compromisso(funcionarios, diaReuniao, idLider, idTarefa);

            /* se o líder não puder, desmarca reunião e apaga */
            if((marca_compromisso_agenda(funcionarios[idLider].agenda, diaReuniao, novoCompr)) != 1) {
                printf("\tLIDER INDISPONIVEL \n");
                destroi_compromisso(novoCompr);
            } else {
                printf("\n%s\tMEMBROS: ",novoCompr->descricao);
                int qtdFuncs = aleat(2,6);
                int marcaQuantidade = 0;

                for(int j=0; j<qtdFuncs; j++) {
                    int idFunc = aleat(0,29);

                    if((funcionarios[idFunc].experiencia + aleat(-20, 10)) < funcionarios[idLider].experiencia) {
                        compromisso_t *novoComprFunc = formata_compromisso(funcionarios, diaReuniao, idFunc, idTarefa);
                        
                        if(marca_compromisso_agenda(funcionarios[idFunc].agenda, diaReuniao, novoComprFunc) != 1) {
                            destroi_compromisso(novoComprFunc);
                            printf("IN ");
                        } else {
                            marcaQuantidade++;
                            printf("OK ");   
                        }
                    }
                }

                if(marcaQuantidade == 0){
                    printf(" VAZIA");
                    desmarca_compromisso_agenda(funcionarios[idLider].agenda, diaReuniao, novoCompr);
                    destroi_compromisso(novoCompr);
                }
            }
        }
        
        for (int j = 0; j < 30; j++)
            prox_mes_agenda(funcionarios[j].agenda);
    } while (funcionarios[29].agenda->mes_atual != 1);
    

    // do {    
    //     /* LOOP PRA MARCAR AS 100 REUNIÕES DO MÊS */
    //     for (int i = 0; i < TOTAL_TAREFAS; i++) {

    //         /* ESCOLHER FUNCIONÁRIO ALEATÓRIO DE 1 A 30 */    
    //         int idLider = rand() % 30;

    //         /* ACHAR UM LÍDER (30 < valorLiderança < 70) */
    //         while ((funcionarios[idLider].lideranca > 29) && (funcionarios[idLider].lideranca < 71))
    //             idLider = rand() % 30;

    //         /* GERA DIA E ID ALEATÓRIOS, DAÍ CRIA COMPROMISSO */
    //         int diaReuniao = rand() % (31) + 1;
    //         zera_vetor(vetIdTarefa, TOTAL_TAREFAS);
    //         compromisso_t *novoCompr = formata_compromisso(funcionarios, diaReuniao, idLider, gera_id_tarefas(vetIdTarefa));

    //         marca_compromisso_agenda(funcionarios[idLider].agenda, diaReuniao, novoCompr);

    //         /* SE A AGENDA DO LÍDER ESTIVER DISPONÍVEL, PROCURA 2-6 FUNCIONÁRIOS PRA MESMA TAREFA */
    //         if (marca_compromisso_agenda(funcionarios[idLider].agenda, diaReuniao, novoCompr)) {
    //             int marcaDisponibilidade = 0;
    //             int nFuncionariosAleat = (rand() % 5) + 2;

    //             printf("\n%s\tMEMBROS: ",novoCompr->descricao);

    //             for (int j = 0; j < nFuncionariosAleat; j++) {
    //                 int funcAleat = rand() % 30;
                    
    //                 /* bigode aqui embaixo */
    //                 if ((funcionarios[funcAleat].experiencia + (rand() % 31) - 20) < funcionarios[idLider].lideranca) {
    //                     printf(" %.2d:",funcAleat);
                        
    //                 /* bigode aqui embaixo */
    //                     if (marca_compromisso_agenda(funcionarios[funcAleat].agenda, diaReuniao, novoCompr)) {
    //                         marcaDisponibilidade++;
    //                         printf("OK ");   
    //                     } else {
    //                         printf("IN ");
    //                     }
    //                 }
    //             }                

    //             /* SE NENHUM FUNCIONÁRIO PUDER PARTICIPAR, DESMARCA A REUNIÃO DO LÍDER */
    //             if(!marcaDisponibilidade) {
    //                 desmarca_compromisso_agenda(funcionarios[idLider].agenda, diaReuniao, novoCompr);
    //                 printf(" VAZIA");
    //             }
            
    //         } else 
    //             printf("\tLIDER INDISPONIVEL");     
    //     }   
        
    //     for (int j = 0; j < 30; j++)
    //         prox_mes_agenda(funcionarios[j].agenda);
    // } while (funcionarios[29].agenda->mes_atual != 1);  

/* FINAL DA INICIALIZAÇÃO DAS PARADAS  -------------------------------------------------------- */

    /* volta todos os funcionários pro mês 1*/
    for (int i = 0; i < TOTAL_FUNCIONARIOS; i++)
        prim_mes_agenda(funcionarios[i].agenda);
    
    int reunioesTotais = 0;
    compromisso_t *listaCompr;
    dia_t *aux;

    /* LOOP DE CADA DIA DO ANO PARA REALIZAR AS REUNIÕES */
    for (int k = 1; k <= MESES_ANO; k++) {
        for (int i = 1; i <= DIAS_MES; i++) {
        
            /* LOOP DE CADA FUNCIONÁRIO */
            for (int j = 0; j < TOTAL_FUNCIONARIOS; j++) {
                aux = funcionarios[j].agenda->ptr_mes_atual->dias;
                listaCompr = funcionarios[j].agenda->ptr_mes_atual->dias->comprs;
                int t = aux->comprs->id;

                if (listaCompr != NULL) {
                    while ((aux->dia <= i) && (listaCompr != NULL)) {
                        
                        if (aux->dia == i) {
                            if (tarefas[t].tempo_conclusao > 0) {
                                tarefas[t].tempo_conclusao -= (listaCompr->inicio - listaCompr->fim) * (funcionarios[j].experiencia / 100.0) * ((100 - tarefas[t].dificuldade) / 100.0);
                                reunioesTotais++;
                                printf("\n%.2d/%.2d F %.2d: %s \n\tT %.2d D %.2d TCR %.2d\n",i,funcionarios[j].agenda->mes_atual,j,listaCompr->descricao,listaCompr->id, tarefas[listaCompr->id].dificuldade, tarefas[listaCompr->id].tempo_conclusao);
                            } else {
                                if (funcionarios[j].experiencia < 100)
                                    funcionarios[j].experiencia++;

                                printf("%.2d/%.2d F %.2d: %s \n\tT %.2d CONCLUIDA\n",i,funcionarios[j].agenda->mes_atual,j,listaCompr->descricao,listaCompr->id);
                            }
                        }

                        listaCompr = listaCompr->prox;
                    }
                }   
            }
        }

        for (int j = 0; j < 30; j++)
            prox_mes_agenda(funcionarios[j].agenda);
    }

    printf("REUNIOES REALIZADAS %.2d\n", reunioesTotais);
    printf("TAREFAS CONCLUIDAS %.2d\n", TOTAL_TAREFAS);
    
    return 0;
}
