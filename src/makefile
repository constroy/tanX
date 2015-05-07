CXX=g++
CXXFLAGS=-O2
LIBS=-lSDL -lSDL_ttf -lSDL_mixer
SRC=$(wildcard *.cxx)
HEAD=$(wildcard *.hxx)
OBJ=$(SRC:.cpp=.o)
EXE=game

all: $(OBJ) $(HEAD)
	@$(CXX) $(OBJ) $(CXXFLAGS) $(LIBS) -o $(EXE)
clean:
	rm -f *.o *.gch $(EXE)
