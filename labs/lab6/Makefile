#@author Wahhaj Javed, muj975, 11135711
#@date 2024-10-31


build_dir = ./build

CC = gcc
CFLAGS = -std=gnu90 -Wall -pedantic -g
CPPFLAGS = -I. -I/student/cmpt332/pthreads 

compile = $(CC) $(CFLAGS) $(CPPFLAGS)
link = -L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads
link += -L$(build_dir) -lMonitor
link += -L$(build_dir) -llist



best_fit: $(build_dir)/best_fit.o $(build_dir)/best_fit_monitor.o \
			$(build_dir)/libMonitor.a $(build_dir)/liblist.a
	$(compile) -o best_fit \
	$(build_dir)/best_fit.o $(build_dir)/best_fit_monitor.o \
	$(link)

$(build_dir)/best_fit.o: best_fit.c | makedir
	$(compile) -o $(build_dir)/best_fit.o -c best_fit.c

$(build_dir)/best_fit_monitor.o: best_fit_monitor.c best_fit_monitor.h|makedir
	$(compile) -o $(build_dir)/best_fit_monitor.o -c best_fit_monitor.c



###############################
######### Monitor #############

$(build_dir)/libMonitor.a: $(build_dir)/Monitor.o
	ar -rcs $(build_dir)/libMonitor.a $(build_dir)/Monitor.o

$(build_dir)/Monitor.o: Monitor.c Monitor.h
	$(compile) -o $(build_dir)/Monitor.o -c Monitor.c 

###############################
######### List ################

list_objs = $(build_dir)/list_movers.o \
			$(build_dir)/list_adders.o \
			$(build_dir)/list_removers.o

$(build_dir)/liblist.a: $(list_objs)
	ar -rcs $(build_dir)/liblist.a $(list_objs) 

$(build_dir)/list_movers.o: list_movers.c list.h | makedir
	$(compile) -o $(build_dir)/list_movers.o -c list_movers.c

$(build_dir)/list_adders.o: list_adders.c list.h | makedir
	$(compile) -o $(build_dir)/list_adders.o -c list_adders.c

$(build_dir)/list_removers.o: list_removers.c list.h | makedir
	$(compile) -o $(build_dir)/list_removers.o -c list_removers.c



makedir: 
	mkdir -p $(build_dir)

.PHONY: clean
clean: 
	rm -rf $(build_dir) best_fit

