#@author Wahhaj Javed, muj975, 11135711
#@date 2024-12-05

obj-m += pipe-driver.o
PWD := $(CURDIR)

CC = gcc
CFLAGS = -g -std=gnu90 -Wall -pedantic
compile = $(CC) $(CFLAGS) $(CPPFLAGS) -I.

all: driver-PC modules

modules:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

driver-PC: driver-PC.o
	$(compile) -o driver-PC driver-PC.o -lm

driver-PC.o : driver-PC.c
	$(compile) -o driver-PC.o -c driver-PC.c

clean:
	rm -f driver-PC driver-PC.o
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean



