CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
INCLUDE = -I. -I/student/cmpt332/pthreads
compile = ${CC} -c ${CFLAGS} ${CPPFLAGS} ${INCLUDE}


arch = $(shell uname -m)
kernel = $(shell uname -s)

# directories
build_dir = ./build
obj_dir = ${build_dir}/obj/${arch}-${kernel}
lib_dir = ${build_dir}/lib/${arch}-${kernel}
bin_dir = ${build_dir}/bin/${arch}-${kernel}

#$(info INFO -- arch is ${arch})
#$(info INFO -- kernel is ${kernel})
#$(info INFO -- build_dir is ${build_dir})
#$(info INFO -- obj_dir is ${obj_dir})
#$(info INFO -- lib_dir is ${lib_dir})
#$(info INFO -- bin_dir is ${bin_dir})


# archive

${lib_dir}/linux-lib.a: ${obj_dir}/linux-lib.o
	ar rcs ${lib_dir}/linux-lib.a ${obj_dir}/linux-lib.o


# object files

${obj_dir}/linux-lib.o: linux-lib.c lab1.h
	$(compile) -o ${obj_dir}/linux-lib.o linux-lib.c

${obj_dir}/sample-linux.o: sample-linux.c lab1.h
	$(compile) -o ${obj_dir}/sample-linux.o sample-linux.c


#PHONY rules

.PHONY: clean mkdirs

mkdirs:
	mkdir -p ${build_dir} ${obj_dir} ${lib_dir} ${bin_dir}

clean:
	rm -rf ${build_dir}