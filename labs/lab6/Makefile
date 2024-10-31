# @author Nakhba Mubashir, epl482, 11317060

.PHONY: all clean


CC=gcc
CFLAGS= -I. -I/student/cmpt332/rtt/include -I/usr/include/tirpc
CPPFLAGS=-std=gnu90 -Wall -pedantic -g
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

LINK_RT_X86=-L/student/cmpt332/rtt/lib/Linuxx86_64 -lRtt -lRttUtils 

Link_Libs=-ltirpc -L. -l:liblist.a $(LINK_RT_X86) 

monitor: reader-writer.o reader-writer-monitor.o monitor.o
	$(CC) -o monitor reader-writer.o reader-writer-monitor.o monitor.o \
	$(Link_Libs)

reader-writer.o: reader-writer.c reader-writer-monitor.h
	 $(compile) -o reader-writer.o -c reader-writer.c

reader-writer-monitor.o: reader-writer-monitor.c monitor.h
	$(compile) -o reader-writer-monitor.o -c reader-writer-monitor.c 

monitor.o: monitor.c monitor.h
	$(compile) -o monitor.o -c monitor.c

clean:
	rm -rf *.o monitor
