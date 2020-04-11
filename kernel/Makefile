DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

OBJDIR?=
SRCDIR?=.

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

CFLAGS:=$(CFLAGS)
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude -Iarch/$(HOSTARCH) -ffreestanding -Wall -Wextra
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
$(OBJDIR)/kernel/kernel.o \

OBJS=\
$(OBJDIR)/$(ARCHDIR)/crti.o \
$(OBJDIR)/$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(OBJDIR)/$(ARCHDIR)/crtend.o \
$(OBJDIR)/$(ARCHDIR)/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(OBJDIR)/$(ARCHDIR)/crti.o \
$(OBJDIR)/$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(OBJDIR)/$(ARCHDIR)/crtend.o \
$(OBJDIR)/$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: cozyos.kernel

cozyos.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $(OBJDIR)/$@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $(OBJDIR)/cozyos.kernel

$(OBJDIR)/$(ARCHDIR)/crtbegin.o $(OBJDIR)/$(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $(abspath $<) -o $@ $(CFLAGS) $(CPPFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -MD -c $(abspath $<) -o $@ $(CPPFLAGS) $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) -MD -c $(abspath $<) -o $@ $(CFLAGS) $(CPPFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	@mkdir -p $(dir $@)
	nasm $(abspath $<) -f elf -o $@

clean:
	rm -f cozyos.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: cozyos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(OBJDIR)/cozyos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
