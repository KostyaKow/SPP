SRC=src
CC=g++
LDFLAGS= -std=gnu++0x
CFLAGS= -std=gnu++0x -c #-Wall
SOURCES=$(SRC)/SError.cpp $(SRC)/SList.cpp $(SRC)/SSexps.cpp $(SRC)/SStateMachine.cpp $(SRC)/SStr.cpp $(SRC)/main.cpp
OBJECTS=$(SOURCES::.cpp=.o)
EXE=spp


default: all

clean:
	rm -r obj/ bin/ *~ src/*~ *.layout *.depend spp

all: $(SOURCES) $(EXE) 


$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
