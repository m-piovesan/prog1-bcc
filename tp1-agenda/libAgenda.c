#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "libAgenda.h"
#define HORAS_DO_DIA 24
#define DIAS_DO_ANO 365

/* esta função transforma uma data lida pelo usuário para uma struct data
 * em uma data do tipo struct tm definida pela biblioteca time.h. 
 * Esta data é então transformada em segundos com a função mktime, para que
 * os outros membros da struct sejam preenchidos automaticamente, e então
 * reconvertida para uma data do tipo struct tm, reescrevendo a variável 
 * original. Com isso, pode-se obter o membro tm_yday, que representa o
 * dia do ano representado pela data: um inteiro entre 0 e 364 */
int obtemDiaDoAno(struct data d) {
	struct tm tipodata;
	time_t segundos;
	int dia_do_ano;

	tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes-1;
    tipodata.tm_year = d.ano-1900;
    tipodata.tm_isdst = -1;
	tipodata.tm_hour = 0;

	/* converte data para época, isto é, segundos desde 1970 */
	segundos = mktime(&tipodata);
	/* converte época em data, obtendo assim automaticamente
	 * o campo 'dia do ano' (tm_yday) que será o índice do
	 * vetor necessário para marcar um compromisso */
	tipodata = *localtime(&segundos);
	/* da reconversão da data, obtém o dia do ano, um número
	 * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;
	
	return dia_do_ano;
}

/* DAQUI PARA BAIXO É COM VOCÊS! SIGAM O ENUNCIADO E O HEADER DISPONÍVEL */

struct agenda criaAgenda(int ano) {
	struct agenda ag;

	ag.ano = ano;
	
	for (int i = 0; i < DIAS_DO_ANO; i++) {
		for (int j = 0; j < HORAS_DO_DIA; j++) {
			ag.agenda_do_ano[i].horas[j] = 0;
		}		
	}

	return ag;

}

/* le um compromisso passado pelo usuario, com data completa e hora pretendida. 
 * Cabe ao usuario desta funcao validar a data e hora do compromisso */
struct compromisso leCompromisso() {
	struct compromisso cpm;
	
	scanf("%d",&cpm.data_compr.dia);
	scanf("%d",&cpm.data_compr.mes);
	scanf("%d",&cpm.data_compr.ano);
	scanf("%d",&cpm.hora_compr);

	return cpm;
}

/* dado um compromisso, retorna a hora definida */
int obtemHora(struct compromisso compr) {
	return compr.hora_compr;
}

/* retorna o ano atribuido a uma agenda criada */
int obtemAno(struct agenda ag) {
	return ag.ano;
}

/* Valida uma data lida do usuario; Retorna 1 se a data for valida e 0 caso contrario */
int validaData(struct data d, struct agenda ag) {
	if ((d.ano == ag.ano) && ((d.dia > 0) && (d.dia<32)) && ((d.mes > 0) && (d.mes < 13))) {
	// verificacao de dias de cada mes
		/* meses com 31 dias */
		if (((d.mes == 1) || (d.mes == 3) || (d.mes == 5) || (d.mes == 7) || (d.mes == 8) || (d.mes == 10) || (d.mes == 12)) && (d.dia<32)) {
			return 1;
		/* meses com 30 dias */
		} else if (((d.mes == 4) || (d.mes == 6) || (d.mes == 9) || (d.mes == 11)) && (d.dia<31)) {
			return 1;
		/* fevereiro */
		} else if ((d.mes == 2) && (d.dia < 29)) {	
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

/* Retorna 0 se data e horario já estiverem ocupados, 1 se data e horario estiverem livres */
int verificaDisponibilidade(struct compromisso compr, struct agenda ag) {
	if ((compr.data_compr.ano == ag.ano) && (ag.agenda_do_ano[obtemDiaDoAno(compr.data_compr)].horas[compr.hora_compr] == 1)) {
		return 0;
	} else {
		return 1;
	};
}

/* Dada uma agenda e um compromisso valido, isto eh, com data/hora validos, 
 * hora livre e dentro do ano da agenda, muda o valor da hora do compromisso
 * de 0 (livre) para 1 (ocupado). Retorna a nova agenda com o compromisso
 * marcado. */
struct agenda marcaCompromisso(struct agenda ag, struct compromisso compr) {
	ag.agenda_do_ano[obtemDiaDoAno(compr.data_compr)].horas[compr.hora_compr] = 1;
	return ag;
}

/* mostra as datas e horas de todos os compromissos marcados na agenda */
void listaCompromissos(struct agenda ag) {
	for (int i = 0; i < DIAS_DO_ANO; i++) {
		for (int j = 0; j < HORAS_DO_DIA; j++) {
			if (ag.agenda_do_ano[i].horas[j] == 1) {
				printf("\ndia: %d, ano: %d, hora: %d, compromisso!",i,ag.ano,j);
			}
		}
	}
}
