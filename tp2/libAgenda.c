#include <stdio.h>
#include <time.h>
#include "libAgenda.h"

#define LIVRE 0
#define OCUPADA 1

int obtemDiaDoAno(struct data d){
    struct tm tipodata={0};
    time_t segundos;
    int dia_do_ano;

    tipodata.tm_mday = d.dia;
    tipodata.tm_mon = d.mes - 1;
    tipodata.tm_year = d.ano - 1900;
    tipodata.tm_isdst = -1;
    tipodata.tm_hour = 0;

    /* converte data para epoca, isto eh, segundos desde 1970 */
    segundos = mktime(&tipodata);

    /* converte epoca em data, obtendo assim automaticamente
     * o campo 'dia do ano' (tm_yday) que sera o indice do
     * vetor necessario para marcar um compromisso */
    tipodata = *localtime(&segundos);

    /* da reconversao da data, obtem o dia do ano, um numero
     * entre 0 e 364 */
    dia_do_ano = tipodata.tm_yday;

    return dia_do_ano;
}

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

/* dado um compromisso, retorna a hora definida */
int obtemHora(struct compromisso *compr) {
	return compr->hora_compr;
}

/* retorna o ano atribuido a uma agenda criada */
int obtemAno(struct agenda *ag) {
	return ag->ano;
}

int validaData(struct agenda *ag, struct data *d) {
if ((d->ano == ag->ano) && (d->dia>0))
		switch (d->mes) {
// meses com 31 dias:
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (d->dia < 32)
				return 1;
			else
				return 0;
			break;

// meses com 30 dias:
		case 4:
		case 6:
		case 9:
		case 11:
			if (d->dia < 31)
				return 1;
			else
				return 0;
			break;

// fevereiro:
		case 2:
		if (d->dia < 29)
				return 1;
			else
				return 0;
			break;

		default:
			return 0;
			break;
	}
	
	else
		return 0;
}

int validaHora(struct compromisso *compr) {
    if ((compr->hora_compr < HORAS_DO_DIA) && (compr->hora_compr > 0))
        return 1;
    else
        return 0;
}

/* Retorna 0 se data e horario já estiverem ocupados, ou 1 caso contrario */
int verificaDisponibilidade(struct agenda *ag, struct compromisso *compr) {
    if (ag->agenda_do_ano[obtemDiaDoAno(compr->data_compr)].horas[obtemHora(compr)] == OCUPADA) 
		return 0;
	else 
		return 1;
}

void marcaCompromisso(struct agenda *ag, struct compromisso *compr) {
    ag->agenda_do_ano[obtemDiaDoAno(compr->data_compr)].horas[compr->hora_compr] = OCUPADA;
}

/* Le um compromisso do teclado (dia, mes, ano e hora, nesta ordem) 
 * Devolve o compromisso no parametro e retorna 1 se o compromisso
 * eh valido ou 0 caso contrario */
int leCompromisso(struct agenda *ag, struct compromisso *compr) {

	scanf("%d",&compr->data_compr.dia);
	scanf("%d",&compr->data_compr.mes);
	scanf("%d",&compr->data_compr.ano);
	scanf("%d",&compr->hora_compr);

    if (validaData(ag, &compr->data_compr) && (validaHora(compr)) && verificaDisponibilidade(ag, compr)) {
        marcaCompromisso(ag, compr);
        return 1;
    } else
        return 0;
}

void listaCompromissos(struct agenda *ag) {
    for (int i = 0; i < DIAS_DO_ANO; i++) {
		for (int j = 0; j < HORAS_DO_DIA; j++) {
			if (ag->agenda_do_ano[i].horas[j] == 1) {
                printf ("dia: %3d, ", i);
                printf ("ano: %4d, ", obtemAno(ag));
                printf ("hora: %2d, compromisso!\n", j);
            }		        
        }
	}
}
