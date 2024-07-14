obj-m += driver.o

# List other object files that are part of the module
driver-objs := driver.o saver1.o paste.o compile_execute.o call_for_compile_execute.o \
               split_terminal.o open_software.o saver2.o split_terminal_shortcut.o

# Assuming the path to the kernel source is set in KDIR
KDIR := /lib/modules/$(shell uname -r)/build

# Current directory
PWD := $(shell pwd)

# Extra flags for including X11 and XTest libraries
EXTRA_CFLAGS += -I/usr/include/X11 -I/usr/include/X11/extensions -I/usr/include/X11/xclip
LDFLAGS_split_terminal.o := -lX11 -lXtst -lxlip

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean