obj-m += range_sequence.o

all:
	make -C /usr/src/linux-headers-$(shell uname -r) M=$(shell pwd) modules

clean:
	make -C /usr/src/linux-headers-$(shell uname -r) M=$(shell pwd) clean
