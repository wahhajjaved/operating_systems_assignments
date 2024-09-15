# author Wahhaj Javed, muj975, 11135711
# author Nakhba Mubashir, epl482, 11317060



kernel := $(shell uname -s)
arch := $(shell uname -m)
ifeq (${kernel}, Linux)
    os = Linux
else ifeq ($(findstring MINGW, ${kernel}), MINGW)
    os = Windows
else
    $(error Only Window and Linux are supported in this make file)
endif

#################################
########## Directories ##########
build_dir = ./build
obj_dir := ${build_dir}/obj
lib_dir := ${build_dir}/lib



##############################
########## Compiler ##########
CC=gcc
CFLAGS=-g -I.
CPPFLAGS=-std=gnu90 -Wall -Wextra -pedantic
compile = ${CC} ${CFLAGS} ${CPPFLAGS} ${I}

###########################
########## All ##########

ifeq ($(os), Windows)
    all_exes = partA1
else ifeq ($(os), Linux)
    all_exes = partA2 partA3 mytestlist
else
    $(error Only Window and Linux are supported in this make file)
endif
$(info Making $(all_exes))

.PHONY: all
all: $(all_exes)
	

############################
########## Part A ##########

partA1: partA1.o square.o
	${CC} ${CFLAGS} ${CPPFLAGS} -o partA1 partA1.o square.o

partA2:
	$(error "Target partA2 not yet implemented.")

partA3:
	$(error "Target partA3 not yet implemented.")

partA1.o: partA1.c square.h
	${compile} -c partA1.c -o partA1.o

square.o: square.c square.h
	${compile} -c square.c -o square.o



# # PART C (linux)
# BUILD_PART_C=build/PartC/

# #if the tarrget is linux
# ifeq ($(UNAME),Linux)
# # directory for PARTC
# 	mkdir -p $(BUILD_PART_C)

# #excecutable
# 	mytestlist: $(BUILD_PART_C)mytestlist.o $(BUILD_PART_C)liblist.a
# 		$(CC) $(CFLAGS) $(CPPFLAGS) -o mytestlist $(BUILD_PART_C)mytestlist.o\
#  $(BUILD_PART_C)liblist.a

# # library
# 	$(BUILD_PART_C)liblist.a: $(BUILD_PART_C)/list_movers.c \
# $(BUILD_PART_C)/list_adders.c $(BUILD_PART_C)/list_removers.c
# 	    ar -c -r -s $(BUILD_PART_C)liblist.o $(BUILD_PART_C)/list_movers.c \
# $(BUILD_PART_C)/list_adders.c $(BUILD_PART_C)/list_removers.c

# #object files
# 	$(BUILD_PART_C)mytestlist.o: mytestlist.c list.h
#     	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)mytestlist.o -c \
# mytestlist.c

# 	$(BUILD_PART_C)list_movers.o: list_movers.c list.h
#         $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)list_movers.o -c \
# list_movers.c

# 	$(BUILD_PART_C)list_adders.o: list_adders.c list.h
#         $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)list_adders.o -c \
# list_adders.c

# 	$(BUILD_PART_C)list_removers.o: list_removers.c list.h
#         $(CC) $(CFLAGS) $(CPPFLAGS) -o $(BUILD_PART_C)list_removers.o -c \
# list_removers.c

# #clean

# 	clean: rm -rf mytestlist
# else
# 	$(error "ERROR: it must be Linux to comple mytestlist.c")
# endif


