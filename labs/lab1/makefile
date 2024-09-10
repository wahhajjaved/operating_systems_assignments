CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic

arch = $(shell uname -m)
kernel = $(shell uname -s)

# directories
build_dir =./build
obj_dir = ${build_dir}/obj/${arch}-${kernel}
lib_dir = ${build_dir}/lib/${arch}-${kernel}
bin_dir = ${build_dir}/bin/${arch}-${kernel}

$(info arch is ${arch})
$(info kernel is ${kernel})
$(info build_dir is ${build_dir})
$(info obj_dir is ${obj_dir})
$(info lib_dir is ${lib_dir})
$(info bin_dir is ${bin_dir})

.PHONY: clean

clean:
	rm -rf ${build_dir}