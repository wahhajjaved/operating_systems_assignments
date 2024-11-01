# @author Nakhba Mubashir, epl482, 11317060

.PHONY: all clean
all: BestFitMonitor

CC=gcc
CFLAGS= -I. -I/student/cmpt332/pthreads -I/student/cmpt332/rtt\
		 -I/usr/include/tirpc 
CPPFLAGS=-std=gnu90 -Wall -pedantic -g
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

Link_Libs=L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads

BestfitMonitor: BestFitMon.o BestFit.o libMonitor.a
	$(CC) -o BestfitMonitor -c -o BestFitMon.o BestFit.o $(Link_Libs) \
		-Lbuild -lMonitor 

libMonitor.a: monitor.o
	ar -rcs libMonitor.a monitor.o

monitor.o: monitor.c monitor.h
	$(compile) -o monitor.o -c monitor.c

clean:
	rm -rf *.o monitor
