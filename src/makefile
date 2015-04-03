CC=g++
CFLAGS=-Wall
LNFLAGS=-lSDL -lSDL_ttf
SRC=$(wildcard *.cpp)
HEAD=$(wildcard *.hpp)
OBJ=$(SRC:.cpp=.o)
EXE=main

all: $(OBJ) $(HEAD)
	@$(CC) $(OBJ) $(CFLAGS) $(LNFLAGS) -o $(EXE)

clean:
	rm -f *.o *.gch $(EXE)
count:
	@echo "wc $(SRC) $(HEAD)"