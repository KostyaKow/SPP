CC=gcc
CFLAGS=-std=c99 -Wall #-Wall -Wextra -pedantic

default: main.o sexps.o misc.o
	$(CC) $(CFLAGS) misc.o main.o sexps.o tree.o -o spp

main.o: main.c tree.c misc.c
	$(CC) $(CFLAGS) -c main.c tree.c misc.c

sexps.o: sexps.c
	$(CC) $(CFLAGS) -c sexps.c

misc.o: misc.c tree.c
	$(CC) $(CFLAGS) -c misc.c tree.c

samples:
	cd samples; make


all: default samples

clean:
	rm -rf *.o spp *.swp *~
