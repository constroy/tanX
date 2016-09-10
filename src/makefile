CXX=g++
CXXFLAGS=-std=c++14 -O2
LIBS=-lSDL -lSDL_mixer
SRC=$(filter-out server.cxx,$(wildcard *.cxx))
HEAD=$(wildcard *.hxx)
OBJ=$(SRC:.cxx=.o)

.PHONY: all

all: tanX lnX

tanX: $(OBJ)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(OBJ)

lnX: server.cxx
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ): $(HEAD)
	$(CXX) -c $(CXXFLAGS) $(SRC)

.PHONY: clean

clean:
	rm -f *.o *.gch tanX lnX
