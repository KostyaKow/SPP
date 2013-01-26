# WARNING: Do not use this Makefile on Windows.
# Use the Code::Blocks project.
# Also, on Windows you should download & 
# install the newest version of MinGW from their website;
# MinGW that comes with Code::Blocks is 
# too old, and can't handle some of the 
# C++11 features used in the code.
# Or better yet, switch to Linux and use Emacs or Vi ;) 

SRC=src
CC=g++
LDFLAGS= -std=gnu++0x
CFLAGS= -std=gnu++0x -c -O3 #-Wall
#TODO: Check if -O3 is necessary, and does it really work better?
SOURCES=$(SRC)/SError.cpp $(SRC)/SList.cpp $(SRC)/SSexps.cpp $(SRC)/SStateMachine.cpp $(SRC)/SStr.cpp $(SRC)/main.cpp
OBJECTS=$(SOURCES::.cpp=.o)
EXE=spp


#I am really tired, so this is ugly
default: all

#ughh
clean:
	rm -r obj/ bin/ *~ src/*~ *.layout *.depend spp

all: $(SOURCES) $(EXE) 


$(EXE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
