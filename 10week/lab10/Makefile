CC=gcc
CFLAGS=-g
BITS := $(shell getconf LONG_BIT)

all: prob1 prob2 prob3 

prob1: prob1.c
	@echo "building for" $(BITS)"-bit machine"
ifeq ($(BITS),64)
	$(CC) $(CFLAGS) -o $@ prob1.c
else
	$(CC) $(CFLAGS) -o $@ prob1.c
endif

prob2: prob2.c
	@echo "building for" $(BITS)"-bit machine"
ifeq ($(BITS),64)
	$(CC) $(CFLAGS) -o $@ prob2.c compute64.o
else
	$(CC) $(CFLAGS) -o $@ prob2.c compute32.o
endif


prob3: prob3.c
	@echo "building for" $(BITS)"-bit machine"
ifeq ($(BITS),64)
	$(CC) $(CFLAGS) -o $@ prob3.c compute64.o
else
	$(CC) $(CFLAGS) -o $@ prob3.c compute32.o
endif

lib: compute.c
	$(CC) -c -m32 -o compute32.o compute.c
	$(CC) -c -m64 -o compute64.o compute.c

clean:
	rm prob1 prob2 prob3
