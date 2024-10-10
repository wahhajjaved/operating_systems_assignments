#@author Wahhaj Javed, muj975, 11135711
#@date 2024-10-10

I = -I/student/cmpt332/rtt/include #-I/student/cmpt332/rtt/src/rtt
# I += -I/student/cmpt332/rtt/src/utils
I += -I/usr/include/tirpc -I/usr/include/tirpc/rpc -I/usr/include
L = -L/student/cmpt332/rtt/lib/Linuxx86_64 -lRtt -lRttUtils -ltirpc -L. -llist

CC =gcc
CFLAGS =-g -I.
CPPFLAGS =-std=gnu90 -Wall -Wextra -pedantic

compile = $(CC) $(CFLAGS) $(CPPFLAGS) $(I)


reader-writer: reader-writer.o reader-writer-monitor.o monitor.o
	$(compile) -o reader-writer reader-writer.o reader-writer-monitor.o \
	monitor.o $(L)

reader-writer.o: reader-writer-monitor.h reader-writer.c
	$(compile) -o reader-writer.o -c reader-writer.c
	
reader-writer-monitor.o: monitor.h reader-writer-monitor.c
	$(compile) -o reader-writer-monitor.o -c reader-writer-monitor.c
	
monitor.o: monitor.h monitor.c
	$(compile) -o monitor.o -c monitor.c


.PHONY: clean
clean:
	rm -f *.o reader-writer
