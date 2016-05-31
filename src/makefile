CXX=g++
CXXFLAGS=-std=c++14 -O2
LIBS=-lSDL -lSDL_ttf -lSDL_mixer
SRC=$(wildcard *.cxx)
HEAD=$(wildcard *.hxx)
OBJ=$(filter-out server.o, $(SRC:.cxx=.o))

all: tanX lnX

tanX: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(OBJ)

lnX: timer.o server.o
	$(CXX) $(CXXFLAGS) -lSDL -o $@ $^

$(OBJ): $(HEAD)
	$(CXX) -c $(CXXFLAGS) $(SRC)

clean:
	rm -f *.o *.gch tanX lnX

.PHONY: clean
