CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Arquivos fonte
SOURCES = main.c liblista_circular.c
HEADERS = liblista_circular.h

# Nome do executável
EXECUTABLE = programa

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
