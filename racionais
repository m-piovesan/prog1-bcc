#include <stdio.h>

// DECLARAÇÃO TIPO RACIONAL
typedef struct {
   int a;
   int b;
} racional;

// FUNÇÃO PRA LER UM RACIONAL
racional leRacional(racional r1) {
   scanf("%d%d",&r1.a,&r1.b);
   return r1;
}

// CÁLCULO DO MDC
int mdc(int a, int b) {
   int resto;
   while (b != 0) {
      resto = a % b;
      a = b;
      b = resto;
   }
   return a;
}


// FUNÇÃO DE SOMA
racional somaRacional(racional r1,racional r2) {
   racional soma; int divi;
   soma.b = (r1.b * r2.b);
   soma.a = ((r1.a * r2.b) + (r2.a * r1.b));

   divi = mdc(soma.a,soma.b);
   soma.a = soma.a/divi;
   soma.b = soma.b/divi;

   return soma;
}

// FUNÇÃO DE SUBTRAÇÃO
racional subRacional(racional r1,racional r2) {
   racional sub; int divi;
   sub.b = (r1.b * r2.b);
   sub.a = ((r1.a * r2.b) - (r2.a * r1.b));

   divi = mdc(sub.a,sub.b);
   sub.a = sub.a/divi;
   sub.b = sub.b/divi;

   return sub;
}

// FUNÇÃO DE MULTIPLICAÇÃO
racional multiRacional(racional r1, racional r2) {
   racional multi; int divi;
   multi.a = (r1.a * r2.a);
   multi.b = (r1.b * r2.b);

   divi = mdc(multi.a,multi.b);
   multi.a = multi.a/divi;
   multi.b = multi.b/divi;

   return multi;   
}

// FUNÇÃO DE DIVISÃO
racional diviRacional(racional r1, racional r2) {
   racional divi; int div;
   divi.a = (r1.a * r2.b);
   divi.b = (r1.b * r2.a);

   div = mdc(divi.a,divi.b);
   divi.a = divi.a/div;
   divi.b = divi.b/div;   

   return divi;   
}

void imprime(racional r1) {
   if (r1.b == 1) {
      printf("%d\n",r1.a);   
   } else if (r1.a == 0) {
      printf("\n0");
   } else {
      printf("%d/",r1.a);
      printf("%d\n",r1.b);
   }
}

int main(void) {
   racional r1,r2, resultado;

   r1 = leRacional(r1);
   r2 = leRacional(r2);

   while ((r1.b != 0) && (r2.b != 0)) {
      printf("\n");

      resultado = somaRacional(r1,r2);
      imprime(resultado);

      resultado = subRacional(r1,r2);
      imprime(resultado);

      resultado = multiRacional(r1,r2);
      imprime(resultado);

      resultado = diviRacional(r1,r2);
      imprime(resultado);

      printf("\n");
      r1 = leRacional(r1);
      r2 = leRacional(r2);
   }

   printf("\n");

   return 0;
}
