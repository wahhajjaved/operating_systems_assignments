obj-m += hello-1.o
driver := 

CC=gcc
CFLAGS=-g -I. 
CPPFLAGS=-std=gnu90 -Wall -pedantic 
compile= $(CC) $(CFLAGS) $(CPPFLAGS)

PWD := $(CURDIR)

all: pipe-driver

pipe-driver: pipe-driver.c
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

driver-PC: driver-PC.c pipe-driver.c 
	{compile} -o driver-PC pipe-driver.c driver-PC.c

driver-PC.o: driver-PC.c 
	{compile} -c driver-PC.c

clean: 
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
