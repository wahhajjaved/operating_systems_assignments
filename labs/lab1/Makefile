# @author Wahhaj Javed, muj975, 11135711
# @date 2024-09-11

# system information
arch = $(shell uname -m)
kernel = $(shell uname -s)

# build directories
build_dir = ./build
obj_dir = ${build_dir}/obj
lib_dir = ${build_dir}/lib

cur_arch_obj_dir = ${obj_dir}/${arch}-${kernel}
cur_arch_lib_dir = ${lib_dir}/${arch}-${kernel}

arm_linux_obj_dir = ${obj_dir}/armv7l-linux
arm_linux_lib_dir = ${lib_dir}/armv7l-linux

ppc_linux_obj_dir = ${obj_dir}/ppc-linux
ppc_linux_lib_dir = ${lib_dir}/ppc-linux

all_dirs = ${build_dir} ${obj_dir} ${lib_dir} ${cur_arch_obj_dir} \
			${cur_arch_lib_dir} ${arm_linux_obj_dir} ${arm_linux_lib_dir} \
			${ppc_linux_obj_dir} ${ppc_linux_lib_dir}


pthreads_path = /student/cmpt332/pthreads



# compiler arguments
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
I = -I. -I${pthreads_path}
compiler = ${CC} ${CFLAGS} ${CPPFLAGS} ${I}



.PHONY: clean clean_all mkdirs all

all: mkdirs sample-linux-${arch} sample-linux-arm sample-linux-ppc



########################
### Current Platform ###

# commands
pthreads_lib_path = ${pthreads_path}/lib/${kernel}${arch}
L = -L${pthreads_lib_path} -L${cur_arch_lib_dir}
link = ${CC} ${CFLAGS} ${CPPFLAGS} ${L}

#executable
sample-linux-${arch}: ${cur_arch_obj_dir}/sample-linux.o \
						${cur_arch_lib_dir}/liblinux-lib.a
	${link} -o sample-linux-${arch} ${cur_arch_obj_dir}/sample-linux.o \
		-lpthreads -llinux-lib


# archive
${cur_arch_lib_dir}/liblinux-lib.a: ${cur_arch_obj_dir}/linux-lib.o
	ar rcs ${cur_arch_lib_dir}/liblinux-lib.a ${cur_arch_obj_dir}/linux-lib.o


# object files
${cur_arch_obj_dir}/linux-lib.o: linux-lib.c lab1.h
	${compiler} -c -o ${cur_arch_obj_dir}/linux-lib.o linux-lib.c

${cur_arch_obj_dir}/sample-linux.o: sample-linux.c lab1.h
	${compiler} -c -o ${cur_arch_obj_dir}/sample-linux.o sample-linux.c



#######################################
###### Cross compile Linuxarmv7l ######

# commands
arm_pthreads_lib_path = ${pthreads_path}/lib/Linuxarmv7l
L_arm = -L${arm_pthreads_lib_path} -L${arm_linux_lib_dir}

compiler_arm = arm-linux-gnueabihf-gcc-10 ${CFLAGS} ${CPPFLAGS} ${I}
link_arm = arm-linux-gnueabihf-gcc-10 ${CFLAGS} ${CPPFLAGS} ${L_arm}

#executable
sample-linux-arm: ${arm_linux_obj_dir}/sample-linux.o \
				${arm_linux_lib_dir}/liblinux-lib.a
	${link_arm} -o sample-linux-arm ${arm_linux_obj_dir}/sample-linux.o \
		-lpthreads -llinux-lib


# archive
${arm_linux_lib_dir}/liblinux-lib.a: ${arm_linux_obj_dir}/linux-lib.o
	ar rcs ${arm_linux_lib_dir}/liblinux-lib.a ${arm_linux_obj_dir}/linux-lib.o


# object files
${arm_linux_obj_dir}/linux-lib.o: linux-lib.c lab1.h
	${compiler_arm} -c -o ${arm_linux_obj_dir}/linux-lib.o linux-lib.c

${arm_linux_obj_dir}/sample-linux.o: sample-linux.c lab1.h
	${compiler_arm} -c -o ${arm_linux_obj_dir}/sample-linux.o sample-linux.c



####################################
###### Cross compile Linuxppc ######

# commands
ppc_pthreads_lib_path = ${pthreads_path}/lib/Linuxppc
L_ppc = -L${ppc_pthreads_lib_path} -L${ppc_linux_lib_dir}

compiler_ppc = powerpc-linux-gnu-gcc-10 ${CFLAGS} ${CPPFLAGS} ${I}
link_ppc = powerpc-linux-gnu-gcc-10 ${CFLAGS} ${CPPFLAGS} ${L_ppc}

#executable
sample-linux-ppc: ${ppc_linux_obj_dir}/sample-linux.o \
					${ppc_linux_lib_dir}/liblinux-lib.a
	${link_ppc} -o sample-linux-ppc ${ppc_linux_obj_dir}/sample-linux.o \
		-lpthreads -llinux-lib


# archive
${ppc_linux_lib_dir}/liblinux-lib.a: ${ppc_linux_obj_dir}/linux-lib.o
	ar rcs ${ppc_linux_lib_dir}/liblinux-lib.a ${ppc_linux_obj_dir}/linux-lib.o


# object files
${ppc_linux_obj_dir}/linux-lib.o: linux-lib.c lab1.h
	${compiler_ppc} -c -o ${ppc_linux_obj_dir}/linux-lib.o linux-lib.c

${ppc_linux_obj_dir}/sample-linux.o: sample-linux.c lab1.h
	${compiler_ppc} -c -o ${ppc_linux_obj_dir}/sample-linux.o sample-linux.c




#PHONY rules

mkdirs:
	mkdir -p ${all_dirs}

clean:
	find ${build_dir} -type f -delete && rm -f sample-linux-x86_64 \
		sample-linux-arm sample-linux-ppc

clean_all:
	rm -rf ${build_dir} sample-linux-x86_64 sample-linux-arm sample-linux-ppc