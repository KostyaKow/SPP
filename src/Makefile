default: main.o sexps.o misc.o
	g++ main.o sexps.o misc.o -o SPP

main.o: main.c
	g++ -c main.c

sexps.o: sexps.c
	g++ -c sexps.c

misc.o: misc/misc.c
	g++ -c misc/misc.c

clean:
	rm -f main.o; rm -f sexps.o; rm -f misc/misc.o	
