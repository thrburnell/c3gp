CC = g++
CFLAGS= -Wall -g

LINK = $(CC) $(CFLAGS) $^ -o $@
COMP = $(CC) $(CFLAGS) -c -o $@ $<
COMP_ONE = $(CC) $(CFLAGS) $^ -o $@

all: tsp.bin

clean:
	rm -f *.o Chess

.PHONY: all clean

tsp.bin: tsp.cpp
	$(COMP_ONE)