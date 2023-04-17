#include <stdio.h>
#include "libAgenda.h"

int main (void) {

    char teste = 'a';
    
    struct agenda ag;
    struct compromisso compr;
    
    struct agenda *ptrAg = &ag;
    struct compromisso *ptrCompr = &compr;

    printf("--> Entre com o ano:");
    scanf("%d",&ag.ano);
    ag = criaAgenda(ag.ano);

    while (teste != 's') {
        printf("--> Entre com dia, mes, ano e hora:");

        if (leCompromisso(ptrAg, ptrCompr)) 
            printf("Compromisso inserido com sucesso!");
        else
            if (!verificaDisponibilidade(ptrAg, ptrCompr))
                printf("Data/Hora ocupada, compromisso nao inserido");
            else
                printf("Data e/ou hora invalidos, compromisso nao inserido");
                
        printf("\n--> Digite um char qualquer ou s para sair:");
        scanf(" %c",&teste);
    }
    
    listaCompromissos(&ag);
    printf("\n");
    return 0;
}