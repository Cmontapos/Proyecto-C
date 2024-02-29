CC = gcc
CFLAGS = -Wall -Wextra
LIBS = `pkg-config --cflags --libs gtk+-3.0`

.PHONY: all clean

all: p1 p2

p1: proyecto1.c
	$(CC) $(CFLAGS) -o exe proyecto1.c $(LIBS)

p2: proyecto2.c
	$(CC) $(CFLAGS) -o exe proyecto2.c -lm

clean:
	rm -f exe
