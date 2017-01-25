CC=gcc
CFLAGS=-g
INCLUDE=
LIB=

all: mycp mymerge mysplit myencode mydecode

mycp: mycp.c
	$(CC) $(CFLAGS) -o $@ mycp.c

mymerge: mymerge.c
	$(CC) $(CFLAGS) -o $@ mymerge.c

mysplit: mysplit.c
	$(CC) $(CFLAGS) -o $@ mysplit.c

myencode: myencode.c
	$(CC) $(CFLAGS) -o $@ myencode.c

mydecode: mydecode.c
	$(CC) $(CFLAGS) -o $@ mydecode.c

clean:
	rm mycp mymerge mysplit myencode mydecode
