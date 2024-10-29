# @author Wahhaj Javed, muj975, 11135711
# @author Nakhba Mubashir, epl482, 11317060

kernel := $(shell uname -s)
arch := $(shell uname -m)

.PHONY: all clean

all:reader-writer-test dining-philosopher s_chat_$(kernel)$(arch) \
s_chat_Linuxarmv7l s_chat_Linuxppc

mkdirs: 
	mkdir -p $(PartB_dir) $(lib_dir) $(build_list) $(obj_dir)


CC=gcc
CFLAGS= -I. -I/student/cmpt332/pthreads \
		-I/student/cmpt332/rtt/include -I/student/cmpt332/rtt/src/rtt \
		-I/usr/include/tirpc -I/usr/include/tirpc/rpc -I/usr/include 
CPPFLAGS=-std=gnu90 -Wall -pedantic -g
compile= $(CC) $(CFLAGS) $(CPPFLAGS)



LIST_OBJ=build/list/list_adders.o build/list/list_movers.o\
		 build/list/list_removers.o

#linking 

LINK_pthreads=-L/student/cmpt332/pthreads/lib/Linuxx86_64 -lpthreads
LINK_RT_X86=-L/student/cmpt332/rtt/lib/Linuxx86_64 -lRtt -lRttUtils -ltirpc
LINK_RT_PPC=-L/student/cmpt332/rtt/lib/Linuxppc -lRtt -lRttUtils -ltirpc
LINK_RT_ARM=-L/student/cmpt332/rtt/lib/Linuxarmv7l -lRtt -lRttUtils -ltirpc


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

$(build_list)/list_movers.o: list_movers.c list.h | mkdirs
	$(compile) -o $(build_list)/list_movers.o -c list_movers.c

$(build_list)/list_adders.o: list_adders.c list.h | mkdirs
	$(compile) -o $(build_list)/list_adders.o -c list_adders.c

$(build_list)/list_removers.o: list_removers.c list.h | mkdirs
	$(compile) -o $(build_list)/list_removers.o -c list_removers.c

################################################################
###################### Part B ##################################


### Monitor ###

$(lib_dir)/libMonitor.a: $(PartB_dir)/Monitor.o
	ar -rcs $(lib_dir)/libMonitor.a $(PartB_dir)/Monitor.o

$(PartB_dir)/Monitor.o: Monitor.c Monitor.h
	$(compile) -o $(PartB_dir)/Monitor.o -c Monitor.c


#### reader writer ####
reader-writer-test: $(PartB_dir)/reader-writer.o \
	$(PartB_dir)/reader-writer-monitor.o $(lib_dir)/liblist.a\
	$(lib_dir)/libMonitor.a 
	
	$(CC) -o reader-writer-test $(PartB_dir)/reader-writer.o \
		$(PartB_dir)/reader-writer-monitor.o\
		${LINK_pthreads} -L$(lib_dir) -lMonitor -llist

$(PartB_dir)/reader-writer.o: reader-writer.c reader-writer-monitor.h | mkdirs 
	 $(compile) -o $(PartB_dir)/reader-writer.o -c reader-writer.c

$(PartB_dir)/reader-writer-monitor.o: reader-writer-monitor.c\
 		reader-writer-monitor.h Monitor.h | mkdirs
	$(compile) -o $(PartB_dir)/reader-writer-monitor.o -c \
		reader-writer-monitor.c

##########PART B bonus #######################

dining-philosopher: $(PartB_dir)/dining-philosopher.o \
    $(PartB_dir)/dining-philosopher-monitor.o \
    $(lib_dir)/libMonitor.a
	$(CC) -o dining-philosopher $(PartB_dir)/dining-philosopher.o \
        $(PartB_dir)/dining-philosopher-monitor.o \
        ${LINK_pthreads} -L$(lib_dir) -lMonitor 

$(PartB_dir)/dining-philosopher.o: dining-philosopher.c dining-philosopher.h \
	 | mkdirs
	$(compile) -o $(PartB_dir)/dining-philosopher.o -c dining-philosopher.c

$(PartB_dir)/dining-philosopher-monitor.o: dining-philosopher-monitor.c \
    dining-philosopher.h Monitor.h | mkdirs
	$(compile) -c -o $(PartB_dir)/dining-philosopher-monitor.o \
    dining-philosopher-monitor.c




################################################################
###################### Part C ##################################


s_chat_$(kernel)$(arch): $(obj_dir)/s_chat.o
	$(compile) -o s_chat_$(kernel)$(arch) $(obj_dir)/s_chat.o \
	$(LINK_RT_X86) -L$(lib_dir) -llist 

$(obj_dir)/s_chat.o: s_chat.c
	$(compile) -c s_chat.c -o $(obj_dir)/s_chat.o


###############################################################################
###################### Part C Cross Compile Linuxarmv7l #######################
compiler_arm = arm-linux-gnueabihf-gcc-10 $(CFLAGS) $(CPPFLAGS)
list_obj_arm=$(build_list)/list_adders_arm.o $(build_list)/list_movers_arm.o \
			$(build_list)/list_removers_arm.o

s_chat_Linuxarmv7l: $(obj_dir)/s_chat_Linuxarmv7l.o \
					$(lib_dir)/liblist_Linuxarmv7l.a
	$(compiler_arm) -o s_chat_Linuxarmv7l $(obj_dir)/s_chat_Linuxarmv7l.o \
	$(LINK_RT_ARM) -L$(lib_dir) -llist_Linuxarmv7l 

$(obj_dir)/s_chat_Linuxarmv7l.o: s_chat.c
	$(compiler_arm) -c s_chat.c -o $(obj_dir)/s_chat_Linuxarmv7l.o



$(lib_dir)/liblist_Linuxarmv7l.a: ${list_obj_arm}
	ar rcs $(lib_dir)/liblist_Linuxarmv7l.a ${list_obj_arm} 

$(build_list)/list_movers_arm.o: list_movers.c list.h | mkdirs
	$(compiler_arm) -o $(build_list)/list_movers_arm.o -c list_movers.c

$(build_list)/list_adders_arm.o: list_adders.c list.h | mkdirs
	$(compiler_arm) -o $(build_list)/list_adders_arm.o -c list_adders.c

$(build_list)/list_removers_arm.o: list_removers.c list.h | mkdirs
	$(compiler_arm) -o $(build_list)/list_removers_arm.o -c list_removers.c
	
	
	
###############################################################################
###################### Part C Cross Compile PPC ###############################
compiler_ppc = powerpc-linux-gnu-gcc-10 $(CFLAGS) $(CPPFLAGS) $(I)
list_obj_ppc=build/list/list_adders_ppc.o build/list/list_movers_ppc.o\
		 build/list/list_removers_ppc.o

s_chat_Linuxppc: $(obj_dir)/s_chat_Linuxppc.o $(lib_dir)/liblist_Linuxppc.a
	$(compiler_ppc) -o s_chat_Linuxppc $(obj_dir)/s_chat_Linuxppc.o \
	$(LINK_RT_PPC) -L$(lib_dir) -llist_Linuxppc 

$(obj_dir)/s_chat_Linuxppc.o: s_chat.c
	$(compiler_ppc) -c s_chat.c -o $(obj_dir)/s_chat_Linuxppc.o



$(lib_dir)/liblist_Linuxppc.a: ${list_obj_ppc}
	ar -rcs $(lib_dir)/liblist_Linuxppc.a ${list_obj_ppc} 

$(build_list)/list_movers_ppc.o: list_movers.c list.h | mkdirs
	$(compiler_ppc) -o $(build_list)/list_movers_ppc.o -c list_movers.c

$(build_list)/list_adders_ppc.o: list_adders.c list.h | mkdirs
	$(compiler_ppc) -o $(build_list)/list_adders_ppc.o -c list_adders.c

$(build_list)/list_removers_ppc.o: list_removers.c list.h | mkdirs
	$(compiler_ppc) -o $(build_list)/list_removers_ppc.o -c list_removers.c




clean: 
	rm -rf $(PartB_dir) $(lib_dir) $(build_list) $(obj_dir) \
		reader-writer-test dining-philosopher s_chat_$(kernel)$(arch) \
		s_chat_Linuxarmv7l s_chat_Linuxppc
