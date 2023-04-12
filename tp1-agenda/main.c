#include <stdio.h>
#include "libAgenda.h"

int main (void) {
    char teste = 'a';
    struct agenda ag;
    struct compromisso compr;
    
    printf("--> Entre com o ano:");
    scanf("%d",&ag.ano);
    ag = criaAgenda(ag.ano);

    while (teste != 's') {
        printf("--> Entre com dia, mes, ano e hora:");
        compr = leCompromisso();        

        if ((validaData(compr.data_compr,ag) == 0) || (obtemHora(compr) < 0)) {
            printf("Data inválida, compromisso não inserido");
        } else {
            if (verificaDisponibilidade(compr,ag) == 0) {
                printf("Data inválida, compromisso não inserido");
            } else {
                ag = marcaCompromisso(ag,compr);
                printf("Compromisso inserido com sucesso!");
            }
        }
       
        printf("\n-->Digite um char qualquer ou s para sair:");
        scanf(" %c",&teste);
    }
    
    listaCompromissos(ag);
    printf("\n");
    return 0;
}
