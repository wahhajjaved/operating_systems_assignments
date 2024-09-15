# author Wahhaj Javed, muj975, 11135711
# author Nakhba Mubashir, epl482, 11317060

.PHONY: clean all

# PART C (linux)
BUILD_PART_C=build/PartC/
CC=gcc
CFLAGS=-g -I.
CPPFLAGS=-std=gnu90 -Wall -pedantic
UNAME:=$(shell uname)
all:all-$(UNAME)

all-LInux: mytestlist

#if the tarrget is linux
ifeq ($(UNAME),Linux)
# directory for PARTC
	mkdir -p $(BUILD_PART_C)

#excecutable
	mytestlist: $(BUILD_PART_C)mytestlist.o $(BUILD_PART_C)liblist.a
		$(CC) $(CFLAGS) $(CPPFLAGS) -o mytestlist $(BUILD_PART_C)mytestlist.o\
 $(BUILD_PART_C)liblist.a

# library
	$(BUILD_PART_C)liblist.a: $(BUILD_PART_C)/list_movers.c \
$(BUILD_PART_C)/list_adders.c $(BUILD_PART_C)/list_removers.c
	    ar -c -r -s $(BUILD_PART_C)liblist.o $(BUILD_PART_C)/list_movers.c \
$(BUILD_PART_C)/list_adders.c $(BUILD_PART_C)/list_removers.c

#object files
	$(BUILD_PART_C)mytestlist.o: mytestlist.c list.h
    	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)mytestlist.o -c \
mytestlist.c

	$(BUILD_PART_C)list_movers.o: list_movers.c list.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)list_movers.o -c \
list_movers.c

	$(BUILD_PART_C)list_adders.o: list_adders.c list.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)list_adders.o -c \
list_adders.c

	$(BUILD_PART_C)list_removers.o: list_removers.c list.h
        $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)list_removers.o -c \
list_removers.c

#clean
	clean: rm -rf mytestlist
else 
	echo "ERROR: it must be Linux to comple mytestlist.c"
endif


