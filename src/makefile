CXX=g++
CXXFLAGS=-std=c++11 -O2
LIBS=-lSDL -lSDL_ttf -lSDL_mixer
SRC=$(wildcard *.cxx)
HEAD=$(wildcard *.hxx)
OBJ=$(SRC:.cxx=.o)
EXEC=tanX

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $(EXEC) $(OBJ)

$(OBJ): $(HEAD) $(SRC)
	$(CXX) -c $(CXXFLAGS) $(SRC)

clean:
	rm -f *.o *.gch $(EXEC)
