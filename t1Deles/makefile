    
CFLAGS = -Wall  -g  # flags de compilacao
LDFLAGS = 

CC = gcc

# arquivos-objeto
	objects = agenda.o libagenda.o  

all: teste


teste: libagenda.o 
	$(CC) -o teste agenda_teste.o libagenda.o $(LDFLAGS)


libagenda.o: libagenda.c libagenda.h
	$(CC) -c $(CFLAGS) libagenda.c


clean:
	rm -f $(objects) agenda 

