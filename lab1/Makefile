#Nakhba Mubashir
#epl482
#11317060

.PHONY: clean

CC=gcc
CFLAGS=-g
CPPFLAGS=-std= gnu90 -Wall -pedantic

CROSS_COMPILE=arm-linux-gnueabihf-

OBJ_FILES: linux_lib.o sample-linux.o

linux-files: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o linux-files $(OBJ_FILES) -L

linux_lib.o: linux-lib.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) 

sample-linux.o: sample-linux.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o sample-linux.o sample-linux.c 







clean:
	rm -f linux_files 
