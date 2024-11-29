.PHONY: clean dir all

CC = gcc
CFLAGS = -g -I. -I/student/cmpt332/rtt/include -I/usr/include/tirpc
CPPFLAGS = -std=gnu90 -Wall -pedantic

LINK_RTTHREADS = -L/student/cmpt332/rtt/lib/Linuxx86_64 -lRtt -lRttUtils \
                 -ltirpc

all: mem-management-sim


# Directories
OBJ_DIR = build/obj
LIB_DIR = build/lib

# Obj files fom prev assignments and labs
LIST_OBJ = $(OBJ_DIR)/list_adders.o $(OBJ_DIR)/list_movers.o \
           $(OBJ_DIR)/list_removers.o
MONITOR_OBJ = $(OBJ_DIR)/monitor.o

dir:
	mkdir -p $(OBJ_DIR) $(LIB_DIR)


# Libraries
LIST_LIB = $(LIB_DIR)/liblist.a
MONITOR_LIB = $(LIB_DIR)/libmonitor.a 

# Memory Management 
mem-management-sim: $(OBJ_DIR)/mem-management-sim.o \
		$(OBJ_DIR)/mem-management-monitor.o $(MONITOR_LIB) $(LIST_LIB)
	$(CC) -o mem-management-sim $(OBJ_DIR)/mem-management-sim.o \
		$(OBJ_DIR)/mem-management-monitor.o $(LINK_RTTHREADS) \
		-L$(LIB_DIR) -lmonitor -llist -lm

$(OBJ_DIR)/mem-management-sim.o: mem-manage-sim.c mem-management.h dir
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $(OBJ_DIR)/mem-management-sim.o \
	 	mem-manage-sim.c

$(OBJ_DIR)/mem-management-monitor.o: mem-management.c mem-management.h dir
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $(OBJ_DIR)/mem-management-monitor.o \
		 mem-management.c

# List
$(LIST_LIB): $(LIST_OBJ)
	ar -rcs $(LIST_LIB) $(LIST_OBJ)

$(OBJ_DIR)/list_adders.o: list_adders.c list.h dir
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $(OBJ_DIR)/list_adders.o list_adders.c

$(OBJ_DIR)/list_movers.o: list_movers.c list.h dir
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $(OBJ_DIR)/list_movers.o list_movers.c

$(OBJ_DIR)/list_removers.o: list_removers.c list.h dir
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $(OBJ_DIR)/list_removers.o list_removers.c

# Monitor
$(MONITOR_LIB): $(MONITOR_OBJ)
	ar -rcs $(MONITOR_LIB) $(MONITOR_OBJ)

$(OBJ_DIR)/monitor.o: monitor.c monitor.h dir
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $(OBJ_DIR)/monitor.o monitor.c

# Clean
clean:
	rm -rf build mem-management-sim

