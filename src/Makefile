CC=gcc
CFLAGS=-Wall

default: main.o sexps.o misc.o
	$(CC) $(CFLAGS) main.o sexps.o misc.o -o spp

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

sexps.o: sexps.c
	$(CC) $(CFLAGS) -c sexps.c

misc.o: misc/misc.c
	$(CC) $(CFLAGS) -c misc/misc.c

clean:
	rm -rf *.o spp *.swp
