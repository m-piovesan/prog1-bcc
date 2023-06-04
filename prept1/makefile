CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = programa
SRC = liblista_ordenada.c main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
