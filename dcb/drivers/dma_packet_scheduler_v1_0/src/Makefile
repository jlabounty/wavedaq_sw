# name of object file
obj-m := dma_packet_scheduler_v1_0.o

# cross compilation env vars
ARCH := arm
CROSS_COMPILE := arm-poky-linux-gnueabi-

# Set KDIR to kernel source dir
KDIR := /data/work/wavedaq/dcb/kernel/linux-xlnx
PWD := $(shell pwd)

all:
	make  ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) \
				-C $(KDIR) M=$(PWD) modules
