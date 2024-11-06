#@author Wahhaj Javed, muj975, 11135711
#@date 2024-11-06

CC = gcc
CFLAGS = -g -std=gnu90 -Wall -pedantic
compile = $(CC) $(CFLAGS) $(CPPFLAGS) -I. -I/student/cmpt332/pthreads
link = -L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads


Lab3.testsynchproblem: Lab3.synchproblem.o Lab3.testsynchproblem.o
	$(compile) -o Lab3.testsynchproblem Lab3.synchproblem.o \
	Lab3.testsynchproblem.o $(link)

Lab3.testsynchproblem.o: Lab3.testsynchproblem.c Lab3.synchproblem.h
	$(compile) -o Lab3.testsynchproblem.o -c Lab3.testsynchproblem.c

Lab3.synchproblem.o: Lab3.synchproblem.c Lab3.synchproblem.h
	$(compile) -o Lab3.synchproblem.o -c Lab3.synchproblem.c 

.PHONY: clean
clean:
	rm -f *.o *.a Lab3.testsynchproblem