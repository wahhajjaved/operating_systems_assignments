#Nakhba Mubashir
#epl482
#11317060

.PHONY: clean

CC=gcc
CFLAGS=-g
CPPFLAGS=-std= gnu90 -Wall -pedantic
LDFLAGS=ar -c -s -R



CROSS_COMPILE=arm-linux-gnueabihf-

#DIRECTORIES
BUILD_OBJ=./build/obj
BUILD_LIB=./build/lib
BUILD_BIN=./build/bin
ARM=/ARM/
PPC=/PPC/
LIN_64=/LINUX_64/

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
	mkdir -p $(BUILD_OBJ)$(LIN_64)
	mkdir -p $(BUILD_LIB)$(LIN_64)
	mkdir -p $(BUILD_BIN)$(LIN_64)

## libraries

#linux
$(BUILD_LIB)$(LIN_64)linux-lib.a: $(BUILD_OBJ)$(LIN_64)linux-lib.o
	$(LDFLAGS) $(BUILD_LIB)$(LIN_64)linux-lib.a $(BUILD_OBJ)$(LIN_64)linux-lib.o
#linux
$(BUILD_LIB)$(PPC)PPC-lib.a: $(BUILD_OBJ)$(PPC)PPC-lib.o
        $(LDFLAGS) $(BUILD_LIB)$(PPC)PPC-lib.a $(BUILD_OBJ)$(PPC)PPC-lib.o
#linux
$(BUILD_LIB)$(ARM)linux-lib.a: $(BUILD_OBJ)$(ARM)ARM-lib.o
        $(LDFLAGS) $(BUILD_LIB)$(ARM)ARM-lib.a $(BUILD_OBJ)$(ARM)ARM-lib.o


## object files
#linux
$(BUILD_OBJ)$(LIN_64)linux_lib.o: linux-lib.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(LIN_64)linux-lib.o

$(BUILD_OBJ)$(LIN_64)sample-linux.o: sample-linux.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(LIN_64)sample-linux.o 
#PPC
$(BUILD_OBJ)$(PPC)PPC_lib.o: linux-lib.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(PPC)PPC-lib.o

$(BUILD_OBJ)$(PPC)sample-ppc.o: sample-linux.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(PPC)sample-ppc.o
#PPC
$(BUILD_OBJ)$(ARM)ARM_lib.o: linux-lib.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(PPC)ARM-lib.o

$(BUILD_OBJ)$(ARM)sample-ARM.o: sample-linux.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(PPC)sample-ARM.o





clean:
	rm -f all 
