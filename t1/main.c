#include <stdio.h>
#include <stdlib.h>
#include "libagenda.h"

int main() {
    agenda_t* agenda = cria_agenda();

    if (agenda == NULL) {
        printf("Erro ao criar agenda.\n");
        return 1;
    }

    horario_compromisso_t horario = {8, 0, 9, 0};
    horario_compromisso_t horario2 = {9, 1, 10, 0};
    horario_compromisso_t horario3 = {10, 1, 11, 0};
    horario_compromisso_t horario4 = {12, 1, 13, 0};
    horario_compromisso_t horario5 = {7, 31, 7, 51};
    horario_compromisso_t horario6 = {6, 1, 7, 30};
    horario_compromisso_t horario7 = {8, 2, 9, 0};
    horario_compromisso_t horario8 = {21, 0, 22, 0};
    horario_compromisso_t horario9 = {21, 1, 22, 30};
    horario_compromisso_t horario10 = {19, 31, 20, 0};


    compromisso_t* compr1 = cria_compromisso(horario, 10, "Reuniao");
    compromisso_t* compr2 = cria_compromisso(horario2, 20, "Apresentacao");
    compromisso_t* compr3 = cria_compromisso(horario3, 30, "Treinamento");
    compromisso_t* compr4 = cria_compromisso(horario4, 40, "Palestra");
    compromisso_t* compr5 = cria_compromisso(horario5, 50, "Jogo");
    compromisso_t* compr6 = cria_compromisso(horario6, 60, "Show");
    compromisso_t* compr7 = cria_compromisso(horario7, 70, "Show");
    compromisso_t* compr8 = cria_compromisso(horario8, 80, "Show");
    compromisso_t* compr9 = cria_compromisso(horario9, 90, "Show");
    compromisso_t* compr10 = cria_compromisso(horario10, 100, "Show");

    if (compr1 == NULL || compr2 == NULL) {
        printf("Erro ao criar compromisso.\n");
        destroi_agenda(agenda);
        return 1;
    }

    marca_compromisso_agenda(agenda, 0, compr1);

    marca_compromisso_agenda(agenda, 0, compr2);
    
    marca_compromisso_agenda(agenda, 1, compr3);
     
    marca_compromisso_agenda(agenda, 1, compr4);
      
    marca_compromisso_agenda(agenda, 2, compr5);
      
    marca_compromisso_agenda(agenda, 2, compr6);
      
    marca_compromisso_agenda(agenda, 10, compr7);
      
    marca_compromisso_agenda(agenda, 0, compr8);
      
    marca_compromisso_agenda(agenda, 1, compr9);

    marca_compromisso_agenda(agenda, 0, compr10);

    printf("Agenda do mês atual:\n");
    imprime_agenda_mes(agenda);

    desmarca_compromisso_agenda(agenda, 0, compr8);
    desmarca_compromisso_agenda(agenda, 1, compr4);

    printf("Agenda do mês atual:\n");
    imprime_agenda_mes(agenda);

    // if (desmarca_compromisso_agenda(agenda, 0, compr2) != 1) {
    //     printf("Erro ao desmarcar compromisso.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    // if (marca_compromisso_agenda(agenda, 1, compr1) != 1) {
    //     printf("Erro ao marcar compromisso.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    

    int currentMonth = mes_atual_agenda(agenda);
    printf("\nMês atual: %d\n", currentMonth);

    ant_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Mês (anterior): %d\n", currentMonth);

    prox_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("mês: %d\n", currentMonth);

    prox_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("mês: %d\n", currentMonth);
    
    prox_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("mês: %d\n", currentMonth);
    
    prox_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("mês: %d\n", currentMonth);
    
    prox_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("mês: %d\n", currentMonth);
    

    ant_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Mês (anterior): %d\n", currentMonth);
    
    ant_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Mês (anterior): %d\n", currentMonth);
    
    ant_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Mês (anterior): %d\n", currentMonth);


    ant_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Mês (anterior): %d\n", currentMonth);


    // if (marca_compromisso_agenda(agenda, 2, compr2) != 1) {
    //     printf("Erro ao marcar compromisso.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    // horario_compromisso_t horario3 = {8, 10, 9, 30};
    // compromisso_t* compr3 = cria_compromisso(horario3, 3, "Treinamento");

    // if (compr3 == NULL) {
    //     printf("Erro ao criar compromisso.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    // if (marca_compromisso_agenda(agenda, 1, compr3) != -1) {
    //     printf("Erro: Compromisso com horário em conflito foi marcado.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    // if (desmarca_compromisso_agenda(agenda, 2, compr2) != 1) {
    //     printf("Erro ao desmarcar compromisso.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    // printf("\nAgenda do mês atual após desmarcar compromisso:\n");
    // imprime_agenda_mes(agenda);

    // //int currentMonth = mes_atual_agenda(agenda);
    // printf("\nMês atual: %d\n", currentMonth);

    // prox_mes_agenda(agenda);
    // currentMonth = mes_atual_agenda(agenda);
    // printf("Próximo mês: %d\n", currentMonth);

    // ant_mes_agenda(agenda);
    // currentMonth = mes_atual_agenda(agenda);
    // printf("Mês anterior: %d\n", currentMonth);

    prim_mes_agenda(agenda);
    printf("mês atual agenda: %d\n", mes_atual_agenda(agenda));

    compromisso_t* teste = compr_agenda(agenda, 2);
    printf("id: %d\n", teste->id);
    teste = prox_compr(teste);
    printf("id: %d\n", teste->id);

    destroi_agenda(agenda);

    return 0;
}
