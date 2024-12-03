# NAKHBA MUBASHIR, EPL482, 11317060

obj-m += pipe-driver.o
driver = pipe-driver

CC=gcc
CFLAGS=-g -I. 
CPPFLAGS=-std=gnu90 -Wall -pedantic 
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

PWD := $(CURDIR)

all: driver-PC

test: all
	sudo ./driver-PC

pipe-driver: pipe-driver.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod $(driver).ko

driver-PC: pipe-driver driver-PC.o 
	{compile} -o driver-PC  driver-PC.o

driver-PC.o: driver-PC.c 
	{compile} -c driver-PC.c

clean: 
	sudo rmmod $(driver)
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f *.o driver_PC
