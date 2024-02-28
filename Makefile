CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lm -lgsl -lgslcblas

TARGET = errorEsperado
SRC = errorEsperado.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm -f $(TARGET)
