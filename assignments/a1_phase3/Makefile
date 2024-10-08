# @author Wahhaj Javed, muj975, 11135711
# @author Nakhba Mubashir, epl482, 11317060
# @date 2024-09-16



kernel := $(shell uname -s)
arch := $(shell uname -m)
ifeq ($(kernel), Linux)
    os = Linux
else ifeq ($(findstring MINGW, $(kernel)), MINGW)
    os = Windows
else
    $(error Only Window and Linux are supported in this make file)
endif

#################################
########## Directories ##########
build_dir = ./build
obj_dir := $(build_dir)/obj/$(os)-$(arch)
lib_dir := $(build_dir)/lib/$(os)-$(arch)

ubc_pthreads_dir = /student/cmpt332/pthreads
ubc_pthreads_lib_dir := /student/cmpt332/pthreads/lib/$(kernel)$(arch)



##############################
########## Compiler ##########
CC=gcc
CFLAGS=-g -I.
CPPFLAGS=-std=gnu90 -Wall -Wextra -pedantic
compile = $(CC) $(CFLAGS) $(CPPFLAGS) $(I)

###########################
########## All ##########

ifeq ($(os), Windows)
    all_exes = partA1
	partA_exes = PartA1
else ifeq ($(os), Linux)
    all_exes = partA2 partA3 mytestlist-$(kernel)$(arch) \
	testlist-$(kernel)$(arch)
	partA_exes = partA2 partA3
else
    $(error Only Window and Linux are supported in this make file)
endif
$(info Making $(all_exes))

.PHONY: all partA
all: mkdirs $(all_exes)

partA: mkdirs $(partA_exes)
	

############################
########## Part A ##########


a1_objects := $(obj_dir)/partA1.o $(obj_dir)/square.o
a2_objects := $(obj_dir)/partA2.o $(obj_dir)/square.o
a3_objects := $(obj_dir)/partA3.o $(obj_dir)/square.o

partA1: $(a1_objects)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o partA1 $(a1_objects)

partA2: $(a2_objects)
	$(compile)  -L$(ubc_pthreads_lib_dir) -o partA2 $(a2_objects) -lpthreads 

partA3: $(a3_objects)
	$(compile) -o partA3 $(a3_objects) -lpthread

$(obj_dir)/partA1.o: partA1.c square.h
	$(compile) -c partA1.c -o $(obj_dir)/partA1.o

$(obj_dir)/partA2.o: partA2.c square.h
	$(compile) -I$(ubc_pthreads_dir) -c partA2.c -o $(obj_dir)/partA2.o

$(obj_dir)/partA3.o: partA3.c square.h
	$(compile) -c partA3.c -o $(obj_dir)/partA3.o
	
$(obj_dir)/square.o: square.c square.h
	$(compile) -c square.c -o $(obj_dir)/square.o


############################
########## Part C ##########

c_objects := $(obj_dir)/testlist.o $(obj_dir)/mytestlist.o \
    $(obj_dir)/list_movers.o $(obj_dir)/list_adders.o \
    $(obj_dir)/list_removers.o

#excecutable
mytestlist-$(kernel)$(arch): $(c_objects) $(lib_dir)/liblist.a
	$(CC) $(CFLAGS) $(CPPFLAGS) -o mytestlist-$(kernel)$(arch) \
    $(obj_dir)/mytestlist.o $(lib_dir)/liblist.a

testlist-$(kernel)$(arch): $(c_objects) $(lib_dir)/liblist.a
	$(CC) $(CFLAGS) $(CPPFLAGS) -o testlist-$(kernel)$(arch) \
    $(obj_dir)/testlist.o $(lib_dir)/liblist.a

# library
$(lib_dir)/liblist.a: $(c_objects)
	ar -c -r -s $(lib_dir)/liblist.a $(c_objects)

#object files
$(obj_dir)/testlist.o: testlist.c list.h
	$(compile) -o $(obj_dir)/testlist.o -c testlist.c
	
$(obj_dir)/mytestlist.o: mytestlist.c list.h
	$(compile) -o $(obj_dir)/mytestlist.o -c mytestlist.c

$(obj_dir)/list_movers.o: list_movers.c list.h
	$(compile) -o $(obj_dir)/list_movers.o -c list_movers.c

$(obj_dir)/list_adders.o: list_adders.c list.h
	$(compile) -o $(obj_dir)/list_adders.o -c list_adders.c

$(obj_dir)/list_removers.o: list_removers.c list.h
	$(compile) -o $(obj_dir)/list_removers.o -c list_removers.c



#clean
.PHONY: clean clean_all mkdirs

mkdirs:
	mkdir -p $(obj_dir) $(lib_dir)

clean:
	find $(build_dir) -type f -delete && rm -f $(all_exes) partA1.exe \
	partA1 partA2 partA3

clean_all:
	rm -rf $(build_dir) $(all_exes) partA1.exe partA1 partA2 partA3


