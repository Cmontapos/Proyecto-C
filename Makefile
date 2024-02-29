CC = gcc
CFLAGS = -Wall -Wextra
LIBS = `pkg-config --cflags --libs gtk+-3.0`

.PHONY: all clean

all: p1 p2

p1: Proyecto_Gato.c
	$(CC) $(CFLAGS) -o exe Proyecto_Gato.c $(LIBS)

p2: errorEsperado.c
	$(CC) $(CFLAGS) -o exe errorEsperado.c -lm

clean:
	rm -f exe
