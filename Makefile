CC = gcc
CFLAGS = -std=gnu99 -g -Wall

PROGS = example

all: clean $(PROGS)

example: example.c trymap.o
	$(CC) $? $(CFLAGS) -o $@

clean:
	rm -f $(PROGS) *\.o
