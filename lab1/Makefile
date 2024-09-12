#Nakhba Mubashir
#epl482
#11317060

.PHONY: clean

CC=gcc
CFLAGS=-g
CPPFLAGS=-std= gnu90 -Wall -pedantic
LDFLAGS=ar -c -s -r

LINK_86=-L./build/lib/X86/ -l:linux-lib.a -L/student/cmpt332/pthreads/lib/Linuxx86_64/ -l:libpthreads.a
LINK_PPC=-L./build/lib/PPC/ -l:linux-lib.a -L/student/cmpt332/pthreads/lib/Linuxxppc/ -l:libpthreads.a
LINK_RASPI=-L./build/lib/ARM/ -l:linux-lib.a -L/student/cmpt332/pthreads/lib/Linuxarmv6l/ -l:libpthreads.a

CROSS_COMPILE=arm-linux-gnueabihf-

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
sample_linux_x86: $(BUILD_OBJ)$(LIN_86)sample-linux.o $(BUILD_OBJ)$(linux_86)sample-linux.o $(BUILD_OBJ)$(linux_86)sample-raspi.o
	 $(CFLAGS) -o $(BUILD_BIN)$(LIN_86)sample_linux_86.o $(BUILD_OBJ)$(linux_86)sample-linux.o $(BUILD_OBJ)$(linux_86)

sample_linux_PPC: $(BUILD_OBJ)$(PPC)sample-ppc.o $(BUILD_OBJ)$(PPC)PPC_lib.o $(BUILD_OBJ)$(PPC)PPC-lib.a



## libraries
#linux
$(BUILD_LIB)$(LIN_86)linux-lib.a: $(BUILD_OBJ)$(LIN_86)linux-lib.o
	$(LDFLAGS) $(BUILD_LIB)$(LIN_86)linux-lib.a $(BUILD_OBJ)$(LIN_86)linux-lib.o
#ppc
$(BUILD_LIB)$(PPC)PPC-lib.a: $(BUILD_OBJ)$(PPC)PPC-lib.o
        $(LDFLAGS) $(BUILD_LIB)$(PPC)PPC-lib.a $(BUILD_OBJ)$(PPC)PPC-lib.o
#arm
$(BUILD_LIB)$(ARM)raspi-lib.a: $(BUILD_OBJ)$(ARM)raspi-lib.o
        $(LDFLAGS) $(BUILD_LIB)$(ARM)raspi-lib.a $(BUILD_OBJ)$(ARM)raspi-lib.o


## object files
#linux
$(BUILD_OBJ)$(LIN_86)linux_lib.o: linux-lib.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(LIN_86)linux-lib.o

$(BUILD_OBJ)$(LIN_86)sample-linux.o: sample-linux.c lab1.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(LIN_86)sample-linux.o 
#PPC
$(BUILD_OBJ)$(PPC)PPC_lib.o: linux-lib.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(PPC)PPC-lib.o

$(BUILD_OBJ)$(PPC)sample-ppc.o: sample-linux.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(PPC)sample-ppc.o
#ARM
$(BUILD_OBJ)$(ARM)raspi_lib.o: linux-lib.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c linux-lib.c -o $(BUILD_OBJ)$(PPC)raspi-lib.o

$(BUILD_OBJ)$(ARM)sample-raspi.o: sample-linux.c lab1.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -c sample-linux.c -o $(BUILD_OBJ)$(PPC)sample-raspi.o





clean:
	rm -f all 
