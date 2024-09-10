# system information
arch = $(shell uname -m)
kernel = $(shell uname -s)

# directories
build_dir = ./build
obj_dir = ${build_dir}/obj/${arch}-${kernel}
lib_dir = ${build_dir}/lib/${arch}-${kernel}
bin_dir = ${build_dir}/bin/${arch}-${kernel}

# additional paths
pthreads_path = /student/cmpt332/pthreads
pthreads_lib_path = ${pthreads_path}/lib/${kernel}${arch}


CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic

# commands
I = -I. -I${pthreads_path}
L = -L${pthreads_lib_path} -L${lib_dir}
compile = ${CC} -c ${CFLAGS} ${CPPFLAGS} ${I}
link = ${CC} ${CFLAGS} ${CPPFLAGS} ${L}





#$(info INFO -- arch is ${arch})
#$(info INFO -- kernel is ${kernel})
#$(info INFO -- build_dir is ${build_dir})
#$(info INFO -- obj_dir is ${obj_dir})
#$(info INFO -- lib_dir is ${lib_dir})
#$(info INFO -- bin_dir is ${bin_dir})


${bin_dir}/sample-linux: ${obj_dir}/sample-linux.o ${lib_dir}/liblinux-lib.a
	${link} -o ${bin_dir}/sample-linux ${obj_dir}/sample-linux.o -lpthreads -llinux-lib


# archive

${lib_dir}/liblinux-lib.a: ${obj_dir}/linux-lib.o
	ar rcs ${lib_dir}/liblinux-lib.a ${obj_dir}/linux-lib.o


# object files

${obj_dir}/linux-lib.o: linux-lib.c lab1.h
	$(compile) -o ${obj_dir}/linux-lib.o linux-lib.c

${obj_dir}/sample-linux.o: sample-linux.c lab1.h
	$(compile) -o ${obj_dir}/sample-linux.o sample-linux.c


#PHONY rules

.PHONY: clean clean_all mkdirs

mkdirs:
	mkdir -p ${build_dir} ${obj_dir} ${lib_dir} ${bin_dir}

clean:
	find ${build_dir} -type f -delete

clean_all:
	rm -rf ${build_dir}