.PHONY: all clean

CC=gcc
CPPFLAGS=-std=gnu90 -Wall -pedantic -pthread -I. -I/student/cmpt332/pthreads
LINK= -L/student/cmpt332/pthreads/lib/linuxx86_64 -lpthreads
CFLAGS=-g

all: Lab3.syntest

Lab3.syntest: Lab3.testsynchproblem.o Lab3.synchproblem.o
	$(CC) $(CFLAGS) $(CPPFLAGS) -o Lab3.syntest Lab3.testsynchproblem.o\
 Lab3.synchproblem.o -z noexecstack $(LINK)

Lab3.synchproblem.o: Lab3.synchproblem.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o Lab3.synchproblem.o -c Lab3.synchproblem.c

Lab3.testsynchproblem.o: Lab3.testsynchproblem.c
	 $(CC) $(CFLAGS) $(CPPFLAGS) -o Lab3.testsynchproblem.o -c\
 Lab3.testsynchproblem.c


clean:
	rm -f *.o Lab3.syntest

