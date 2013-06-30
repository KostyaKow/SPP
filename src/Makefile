CC=gcc
CFLAGS=-std=c99 -Wall #-Wall -Wextra -pedantic

default: spp

spp: objs
	$(CC) $(CFLAGS) *.o -o spp

objs:
	$(CC) $(CFLAGS) -c *.c

samples:
	cd samples; make


all: default samples

clean:
	rm -rf *.o spp *.swp *~
