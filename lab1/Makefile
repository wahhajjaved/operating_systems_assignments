#Nakhba Mubashir
#epl482
#11317060

.PHONY: clean

CC=gcc
CFLAGS=-g
CPPFLAGS=-std= gnu90 -Wall -pedantic

CROSS_COMPILE=arm-linux-gnueabihf-

#DIRECTORIES
BUILD_OBJ=./build/obj
BUILD_LIB=./build/lib
BUILD_BIN=./build/bin
ARM=/ARM/
PPC=/PPC/

OBJ_FILES: linux_lib.o sample-linux.o

linux-files: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o linux-files $(OBJ_FILES) -L


#directories 
directories:
	mkdir -p $(BUILD_OBJ)$(ARM) 
	mkdir -p $(BUILD_LIB)$(ARM)
	mkdir -p $(BUILD_BIN)$(ARM)
	mkdir -p $(BUILD_OBJ)$(PPC)
	mkdir -p $(BUILD_LIB)$(PPC)
	mkdir -p $(BUILD_BIN)$(PPC) 	

## object files
#normal
linux_lib.o: linux-lib.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) 

sample-linux.o: sample-linux.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o sample-linux.o sample-linux.c 
#






clean:
	rm -f all 
