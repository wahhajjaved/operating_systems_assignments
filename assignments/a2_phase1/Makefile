# @author Wahhaj Javed, muj975, 11135711
# @author Nakhba Mubashir, epl482, 11317060

CC=gcc
CFLAGS=-g -I -I/student/cmpt332/pthreads -I/student/cmpt332/rtt\
		-I/usr/include/tirpc -I/usr/include
CPPFLAGS=-std=gnu90 -Wall -pedantic 
compile= $(CC) $(CFLAGS) $(CPPFLAGS)


LIST_OBJ=build/list/list_adders.o build/list/list_movers.o\
		 build/list/list_removers.o

#linking 

LINK_pthreads=-L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads
LINK_RT_X86=-L/student/cmpt332/rtt/lib/Linuxx86_64 -lRtt
LINK_RT_PPC=-L/student/cmpt332/rtt/lib/Linuxppc -lRtt
LINK_RT_ARM=-L/student/cmpt332/rtt/lib/Linuxarmv7l -lRtt


kernel := $(shell uname -s)
arch := $(shell uname -m)
ifeq ($(kernel), Linux)
    os = Linux
else ifeq ($(findstring MINGW, $(kernel)), MINGW)
    os = Windows
else
    $(error Only Window and Linux are supported in this make file)
endif


#directories

build_dir= ./build
obj_dir := $(build_dir)/obj
lib_dir := $(build_dir)/lib
build_list := $(build_dir)/list
PartB_dir := $(build_dir)/PartB

################################################################

# rules for list library
$(lib_dir)/liblist.a: ${LIST_OBJ}
	ar -rcs $(lib_dir)/liblist.a ${LIST_OBJ} 

$(build_list)/list_movers.o: list_movers.c list.h
	$(compile) -o $(build_list)/list_movers.o -c list_movers.c

$(build_list)/list_adders.o: list_adders.c list.h
	$(compile) -o $(build_list)/list_adders.o -c list_adders.c

$(build_list)/list_removers.o: list_removers.c list.h
	$(compile) -o $(build_list)/list_removers.o -c list_removers.c

################################################################
###################### Part B ##################################

reader-write: 



