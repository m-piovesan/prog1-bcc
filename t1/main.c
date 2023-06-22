#include <stdio.h>
#include <stdlib.h>
#include "libagenda.h"

int main() {
    agenda_t* agenda = cria_agenda();

    if (agenda == NULL) {
        printf("Erro ao criar agenda.\n");
        return 1;
    }

    horario_compromisso_t horario = {8, 10, 9, 30};
    horario_compromisso_t horario2 = {10, 12, 11, 30};

    compromisso_t* compr1 = cria_compromisso(horario, 1, "Reuniao");
    compromisso_t* compr2 = cria_compromisso(horario2, 2, "Apresentacao");

    if (compr1 == NULL || compr2 == NULL) {
        printf("Erro ao criar compromisso.\n");
        destroi_agenda(agenda);
        return 1;
    }

    int currentMonth = mes_atual_agenda(agenda);
    printf("Mês atual: %d\n", currentMonth);

    ant_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Mês anterior: %d\n", currentMonth);

    prox_mes_agenda(agenda);
    printf("teste");
    currentMonth = mes_atual_agenda(agenda);
    printf("Próximo mês: %d\n", currentMonth);

    

    // if (marca_compromisso_agenda(agenda, 1, compr1) != 1) {
    //     printf("Erro ao marcar compromisso.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    // if (marca_compromisso_agenda(agenda, 2, compr2) != 1) {
    //     printf("Erro ao marcar compromisso.\n");
    //     destroi_agenda(agenda);
    //     return 1;
    // }

    printf("Agenda do mês atual:\n");
    imprime_agenda_mes(agenda);

    horario_compromisso_t horario3 = {8, 10, 9, 30};
    compromisso_t* compr3 = cria_compromisso(horario3, 3, "Treinamento");

    if (compr3 == NULL) {
        printf("Erro ao criar compromisso.\n");
        destroi_agenda(agenda);
        return 1;
    }

    if (marca_compromisso_agenda(agenda, 1, compr3) != -1) {
        printf("Erro: Compromisso com horário em conflito foi marcado.\n");
        destroi_agenda(agenda);
        return 1;
    }

    if (desmarca_compromisso_agenda(agenda, 2, compr2) != 1) {
        printf("Erro ao desmarcar compromisso.\n");
        destroi_agenda(agenda);
        return 1;
    }

    printf("\nAgenda do mês atual após desmarcar compromisso:\n");
    imprime_agenda_mes(agenda);

    //int currentMonth = mes_atual_agenda(agenda);
    printf("\nMês atual: %d\n", currentMonth);

    prox_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Próximo mês: %d\n", currentMonth);

    ant_mes_agenda(agenda);
    currentMonth = mes_atual_agenda(agenda);
    printf("Mês anterior: %d\n", currentMonth);

    destroi_agenda(agenda);

    return 0;
}
