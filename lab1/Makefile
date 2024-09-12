#Nakhba Mubashir
#epl482
#11317060

.PHONY: clean

CC=gcc
CFLAGS=-g
CPPFLAGS=-std=gnu90 -Wall -pedantic -I. -I/student/cmpt332/pthreads
LDFLAGS=ar -c -s -r

LINK_86=-L./build/lib/LINUX_86/ -l:linux-lib.a -L/student/cmpt332/pthreads/lib/Linuxx86_64/ -l:libpthreads.a
LINK_PPC=-L./build/lib/PPC/ -l:PPC-lib.a -L/student/cmpt332/pthreads/lib/Linuxxppc/ -l:libpthreads.a
LINK_RASPI=-L./build/lib/ARM/ -l:raspi-lib.a -L/student/cmpt332/pthreads/lib/Linuxarmv6l/ -l:libpthreads.a
CROSS-COMPILE=arm-linux-gnueabihf-


#DIRECTORIES
BUILD_OBJ=./build/obj
BUILD_LIB=./build/lib
BUILD_BIN=./build/bin
ARM=/ARM/
PPC=/PPC/
LIN_86=/LINUX_86/

O_FILES:direct sample_linux_x86 sample_linux_PPC sample_linux_ARM



#directories 
direct:
	mkdir -p $(BUILD_OBJ)$(ARM) 
	mkdir -p $(BUILD_LIB)$(ARM)
	mkdir -p $(BUILD_BIN)$(ARM)
	mkdir -p $(BUILD_OBJ)$(PPC)
	mkdir -p $(BUILD_LIB)$(PPC)
	mkdir -p $(BUILD_BIN)$(PPC) 	
	mkdir -p $(BUILD_OBJ)$(LIN_86)
	mkdir -p $(BUILD_LIB)$(LIN_86)
	mkdir -p $(BUILD_BIN)$(LIN_86)

#excecutable for libraries
sample_linux_x86: $(BUILD_OBJ)$(LIN_86)sample-linux.o $(BUILD_OBJ)$(LIN_86)linux-lib.o $(BUILD_LIB)$(LIN_86)linux-lib.a
	$(CC) $(CFLAGS) -o $(BUILD_BIN)$(LIN_86)sample_linux_x86 $(BUILD_OBJ)$(LIN_86)sample-linux.o $(LINK_86)

sample_linux_PPC: $(BUILD_OBJ)$(PPC)sample-ppc.o $(BUILD_OBJ)$(PPC)PPC-lib.o $(BUILD_OBJ)$(PPC)PPC-lib.a
	$(CC) $(CFLAGS) -o $(BUILD_BIN)$(PPC)sample_linux_PPC $(BUILD_OBJ)$(PPC)sample-ppc.o $(LINK_PPC)

sample_linux_ARM: $(BUILD_OBJ)$(ARM)sample-raspi.o $(BUILD_OBJ)$(ARM)raspi-lib.o $(BUILD_OBJ)$(ARM)raspi-lib.a
	$(CC) $(CFLAGS) -o $(BUILD_BIN)$(ARM)sample_linux_ARM $(BUILD_OBJ)$(ARM)sample-raspi.o $(LINK_RASPI)

## libraries
#linux
$(BUILD_LIB)$(LIN_86)linux-lib.a: $(BUILD_OBJ)$(LIN_86)linux-lib.o
	ar rcs $(BUILD_LIB)$(LIN_86)linux-lib.a $(BUILD_OBJ)$(LIN_86)linux-lib.o
#ppc
$(BUILD_LIB)$(PPC)PPC-lib.a: $(BUILD_OBJ)$(PPC)PPC-lib.o
	ar rcs $(BUILD_LIB)$(PPC)PPC-lib.a $(BUILD_OBJ)$(PPC)PPC-lib.o
#arm
$(BUILD_LIB)$(ARM)raspi-lib.a: $(BUILD_OBJ)$(ARM)raspi-lib.o
	ar rcs $(BUILD_LIB)$(ARM)raspi-lib.a $(BUILD_OBJ)$(ARM)raspi-lib.o

## object files
#linux
$(BUILD_OBJ)$(LIN_86)linux-lib.o: linux-lib.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(LIN_86)linux-lib.o

$(BUILD_OBJ)$(LIN_86)sample-linux.o: sample-linux.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(LIN_86)sample-linux.o 
#PPC
$(BUILD_OBJ)$(PPC)PPC-lib.o: linux-lib.c lab1.h
	$(CC) $(CROSS-COMPILE) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(PPC)PPC-lib.o

$(BUILD_OBJ)$(PPC)sample-ppc.o: sample-linux.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(PPC)sample-ppc.o
#ARM
$(BUILD_OBJ)$(ARM)raspi-lib.o: linux-lib.c lab1.h
	$(CC) $(CROSS-COMPILE) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(ARM)raspi-lib.o

$(BUILD_OBJ)$(ARM)sample-raspi.o: sample-linux.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(ARM)sample-raspi.o





clean:
	rm -f all  
	rm -f $(BUILD_OBJ)$(LIN_86)*.o $(BUILD_OBJ)$(PPC)*.o $(BUILD_OBJ)$(ARM)*.o
	rm -f $(BUILD_BIN)$(LIN_86)* $(BUILD_BIN)$(PPC)* $(BUILD_BIN)$(ARM)*
	rm -f $(BUILD_LIB)$(LIN_86)*.a $(BUILD_LIB)$(PPC)*.a $(BUILD_LIB)$(ARM)*.a

