CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJS = libagenda.o main.o
TARGET = agenda

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

libagenda.o: libagenda.c libagenda.h
	$(CC) $(CFLAGS) -c libagenda.c

main.o: main.c libagenda.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) $(TARGET)
