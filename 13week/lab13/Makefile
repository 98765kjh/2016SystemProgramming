CC=gcc
CFLAGS=-g -pthread -msoft-float
#CFLAGS=-g -pthread
LIB=-lm
INCLUDE=

all: prob1 prob2 prob3

prob1: prob1.c
	$(CC) $(CFLAGS) -o $@ prob1.c $(LIB)

prob2: prob2.c
	$(CC) $(CFLAGS) -o $@ prob2.c $(LIB)

prob3: prob3.c sbuf.c sbuf.h
	$(CC) $(CFLAGS) -o $@ prob3.c sbuf.c $(LIB)

clean:
	rm prob1 prob2 prob3
