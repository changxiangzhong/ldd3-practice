obj-m := helloprocfs.o

helloprocfs-y := main.o

all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

.PHONY: clean
clean:
	    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# Remember to create a char device file
# sudo mknod ./hello-char-dev-2 c 243 2
