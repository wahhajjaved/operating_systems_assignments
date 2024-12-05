#@author Wahhaj Javed, muj975, 11135711
#@date 2024-12-05

obj-m += pipe-driver.o
PWD := $(CURDIR)

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean