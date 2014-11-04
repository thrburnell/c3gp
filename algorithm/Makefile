CC = g++
CFLAGS = -Wall -Wextra -pedantic -g -std=c++11

LINK = $(CC) $(CFLAGS) $^ -o $@
COMP = $(CC) $(CFLAGS) -c -o $@ $<
COMP_ONE = $(CC) $(CFLAGS) $^ -o $@

all: tsp.bin

clean:
	rm -f *.o *.bin

.PHONY: all clean

tsp.bin: tsp.cpp
	$(COMP_ONE)