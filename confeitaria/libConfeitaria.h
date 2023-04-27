#define MAXBOLOS 20
#define MAXTORTAS 10 

typedef struct tipo_data {
	int dia;
	int mes;
	int ano;
} data;

typedef struct tipo_boloPote{
    char tipo;
    data fabrica;
} boloPote;

typedef struct tipo_tortinha{
    int diasConsumo;
    data fabrica;
} tortinha;

typedef struct tipo_frigobar {
    boloPote prateleiraCima[MAXBOLOS];    
    tortinha prateleiraBaixo[MAXTORTAS];
} frigobar;

typedef struct tipo_pedidoDia {
    int pedidosBolo;
    int pedidosTorta;
} pedidoDia;
