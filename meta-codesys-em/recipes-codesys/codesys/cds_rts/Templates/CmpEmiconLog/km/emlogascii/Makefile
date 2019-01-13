# CURRENT = $(shell uname -r)
KDIR = ../../../../../../linux_new/VAR-SOM-AMx3-Kernel-4-x
TARGET1 = emlogascii
CFLAGS_$(TARGET1).o := -DDEBUG

obj-m	:= $(TARGET1).o


default:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- modules

clean:
	@rm -f *.o .*.cmd .*.flags *.mod.c *.order
	@rm -f .*.*.cmd *~ *.*~ TODO.*
	@rm -fR .tmp*
	@rm -rf .tmp_versions

disclean: clean
	@rm *.ko *.symvers
