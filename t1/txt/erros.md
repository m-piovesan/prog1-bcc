# problemas:

* [X] função prox_mes_agenda
* [X] função ant_mes_agenda

* [X] marcar compromisso pra um dia que já tem, quando tem mais de 2 dias mallocados no mês

* [X] quando tenho que mudar o último dia do mês, ele coloca o novo último dia como próx da cabeça

* [X] testa_intersec não tá funcionando (ele não marca mesmo quando não tem conflito de horário)
    -> o b.o tá quando o novo compromisso é o último da lista

* [X] função remove compromisso

=3948== Conditional jump or move depends on uninitialised value(s)
==3948==    at 0x109B6B: imprime_agenda_mes (in /home/piove/Desktop/college/prog1-bcc/t1/agenda)
==3948==    by 0x10A6F7: main (in /home/piove/Desktop/college/prog1-bcc/t1/agenda)
==3948==  Uninitialised value was created by a heap allocation
==3948==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==3948==    by 0x109EF0: ant_mes_agenda (in /home/piove/Desktop/college/prog1-bcc/t1/agenda)
==3948==    by 0x10A6B7: main (in /home/piove/Desktop/college/prog1-bcc/t1/agenda)


* [X] gerar id aleatório, atualmente eles são ordenados de acordo com vetor [0..100]

* lembrar de dar free no vetor que armazena os ID's que já foram 

* colocar comentários explicando as funções auxiliares (cabeçalhos)