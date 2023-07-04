CFLAGS = -Wall -g # flags de compilacao
LDFLAGS = 

CC = gcc

OBJS = libagenda.o libfirma.o
TARGET = agenda

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

libagenda.o: libagenda.c libagenda.h
	$(CC) $(CFLAGS) -c libagenda.c

libfirma.o: libfirma.c libagenda.h
	$(CC) $(CFLAGS) -c libfirma.c

clean:
	rm -f $(OBJS) $(TARGET)
