CC=gcc
CFLAGS=-Wno-unused-but-set-variable -Wno-deprecated-declarations #-Wall -Wextra -pedantic

default: main.o sexps.o misc.o
	$(CC) $(CFLAGS) misc.o main.o sexps.o tree.o -o spp

main.o: main.c misc/tree.c
	$(CC) $(CFLAGS) -c main.c misc/tree.c

sexps.o: sexps.c
	$(CC) $(CFLAGS) -c sexps.c

misc.o: misc/misc.c misc/tree.c
	$(CC) $(CFLAGS) -c misc/misc.c misc/tree.c

clean:
	rm -rf *.o spp *.swp
