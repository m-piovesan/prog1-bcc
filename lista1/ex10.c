#include <stdio.h>
#define tam 5

int main() {

    int v1[tam];
    int pares = 0;
    int impares = 0;

// ler os valores do vetor
    for (int i = 0; i < tam; i++) {
        scanf("%d",&v1[i]);
    }

// ver os que são pares / ímpares e guardar nas var
    for (int i = 0; i < tam; i++) {
        if (v1[i] % 2 == 0)
        {
            pares++;
        } else {
            impares++;
        }
    }

    printf("Pares: %d\nÍmpares: %d\n",pares,impares);

    printf("\n");
    return 0;
}
