#@author Wahhaj Javed, muj975, 11135711
#@date 2024-11-07

CC = gcc
CFLAGS = -g -std=gnu90 -Wall -pedantic
compile = $(CC) $(CFLAGS) $(CPPFLAGS) -I.


pagerep-sim: pagerep-sim.o
	$(compile) -o pagerep-sim pagerep-sim.o -lm
	
pagerep-sim.o : pagerep-sim.c
	$(compile) -o pagerep-sim.o -c pagerep-sim.c

.PHONY: clean
clean:
	rm -f *.o *.a pagerep-sim