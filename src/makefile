CC=g++
CFLAGS=-Wall
LNFLAGS=-lSDL -lSDL_ttf -lSDL_mixer
SRC=$(wildcard *.cpp)
HEAD=$(wildcard *.hpp)
OBJ=$(SRC:.cpp=.o)
EXE=game

all: $(OBJ) $(HEAD)
	@$(CC) $(OBJ) $(CFLAGS) $(LNFLAGS) -o $(EXE)

clean:
	rm -f *.o *.gch $(EXE)
count:
	@echo "wc $(SRC) $(HEAD)"