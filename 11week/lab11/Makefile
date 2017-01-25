CC=gcc
CFLAGS=

all: prob1 prob2

prob1: prob1.c smalloc1.c smalloc1.h
	$(CC) $(CFLAGS) -o $@ prob1.c smalloc1.c

prob2: prob2.c smalloc2.c smalloc2.h
	$(CC) $(CFLAGS) -o $@ prob2.c smalloc2.c

clean:
	rm prob1 prob2 
