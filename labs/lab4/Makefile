# @author Nakhba Mubashir, epl482, 11317060

.PHONY: all clean


CC=gcc
CFLAGS= -I. -I/student/cmpt332/pthreads \
		-I/student/cmpt332/rtt/include -I/student/cmpt332/rtt/src/rtt \
		-I/usr/include/tirpc -I/usr/include/tirpc/rpc -I/usr/include 
CPPFLAGS=-std=gnu90 -Wall -pedantic -g
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

LINK_RT_X86=-L/student/cmpt332/rtt/lib/Linuxx86_64 -lRtt 

Link_Libs= -ltirpc -L. -l:liblist.a $(LINK_RT_X86) 

monitor: reader-writer.o reader-writer-monitor.o monitor.o
	$(CC) -o monitor reader-writer.o reader-writer-monitor.o monitor.o\
	

reader-writer.o: reader-writer.c reader-writer-monitor.h
	 $(compile) -o $(PartB_dir)/reader-writer.o -c reader-writer.c

reader-writer-monitor.o: reader-writer-monitor.c reader-writer-monitor.h
	$(compile) -o reader-writer-monitor.o -c reader-writer-monitor.c 

monitor.o: monitor.c monitor.h
	$(compile) -o monitor.o -c monitor.c

clean:
	rm -rf *.o monitor
