# @author Nakhba Mubashir, epl482, 11317060

.PHONY: all clean
all: BestFitMonitor

CC=gcc
CFLAGS= -I. -I/student/cmpt332/pthreads -I/student/cmpt332/rtt\
		 -I/usr/include/tirpc 
CPPFLAGS=-std=gnu90 -Wall -pedantic -g
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

Link_Libs=-L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads

BestFitMonitor: BestFitMonitor.o BestFit.o libMonitor.a libList.a
	$(CC) -o BestFitMonitor BestFitMonitor.o BestFit.o $(Link_Libs) \
		-L. -lMonitor -lList 

BestFit.o: BestFit.c BestFitMonitor.h
	$(compile) -c -o BestFit.o BestFit.c

BestFitMonitor.o: BestFitMonitor.c BestFitMonitor.h Monitor.h
	$(compile) -c -o BestFitMonitor.o BestFitMonitor.c

# Monitors
libMonitor.a: Monitor.o
	ar -rcs libMonitor.a Monitor.o

Monitor.o: Monitor.c Monitor.h
	$(compile) -o Monitor.o -c Monitor.c

#lists
list_movers.o: list_movers.c list.h
	$(compile) -o list_movers.o -c list_movers.c

list_adders.o: list_adders.c list.h
	$(compile) -o list_adders.o -c list_adders.c

list_removers.o: list_removers.c list.h
	$(compile) -o list_removers.o -c list_removers.c

libList.a: list_movers.o list_adders.o list_removers.o
	ar -rcs libList.a list_movers.o list_adders.o list_removers.o

clean:
	rm -rf *.o *.a BestFitMonitor
