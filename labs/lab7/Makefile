# @author Nakhba Mubashir, epl482, 11317060

.PHONY: all clean
all: sim

CC=gcc
CFLAGS=-g -I. 
CPPFLAGS=-std=gnu90 -Wall -pedantic 
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

#excutable
sim: sim.o
	$(CC) -o sim sim.o -lm

sim.o: sim.c
	$(compile) -c -o sim.o sim.c

clean:
	rm -rf sim.o sim
