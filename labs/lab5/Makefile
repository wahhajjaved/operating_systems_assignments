# @author Nakhba Mubashir, epl482, 11317060

.PHONY: clean

CC=gcc
CFLAGS= -I. -I/student/cmpt332/pthreads
CPPFLAGS=-std=gnu90 -Wall -pedantic -g
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

LINK_PTHREADS_X86=-L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads

Link_Libs=-llist -L. -l:liblist.a $(LINK_PTHREADS_X86) 

all: sim

#excecutable
sim: sim.o
	$(CC) -o sim sim.o $(Link_Libs)

# obj files
sim.o: sim.c
	$(compile) -o sim.o -c sim.c


clean:
	rm -f *.o sim
