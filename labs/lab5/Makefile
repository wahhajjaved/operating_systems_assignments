#@author Wahhaj Javed, muj975, 11135711
#@date 2024-10-10

pthreads_path = /student/cmpt332/pthreads
L = -L. -llist
L += -L$(pthreads_path)/lib/Linuxx86_64 -lpthreads

CC =gcc
CFLAGS =-g -I. -I$(pthreads_path)
CPPFLAGS =-std=gnu90 -Wall -Wextra -pedantic
compile := $(CC) $(CFLAGS) $(CPPFLAGS)

sim: sim.o
	$(compile) -o sim sim.o $(L)

sim.o: sim.c list.h
	$(compile) -c sim.c -o sim.o