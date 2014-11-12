CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -pedantic
BIN = tsp.bin

SRC = $(shell find . -name "*.cpp")
OBJ = $(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

%.o: %.c
	$(CXX) $@ -c

clean:
	rm -f *.o
	rm -f $(BIN)
	rm -f lib/gason/*.o
