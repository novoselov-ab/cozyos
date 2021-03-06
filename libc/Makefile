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
INCLUDEDIR?=$(PREFIX)/include
LIBDIR?=$(EXEC_PREFIX)/lib

CFLAGS:=$(CFLAGS)
CPPFLAGS:=$(CPPFLAGS) -D__is_libc -Iinclude -ffreestanding -Wall -Wextra
LIBK_CFLAGS:=$(CFLAGS)
LIBK_CPPFLAGS:=$(CPPFLAGS) -D__is_libk
LIBK_CXXFLAGS:=$(CXXFLAGS)

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS:=$(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS:=$(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS=\
$(ARCH_FREEOBJS) \
$(OBJDIR)/stdio/stdio.o \
$(OBJDIR)/stdlib/stdlib.o \
$(OBJDIR)/string/string.o \

HOSTEDOBJS=\
$(ARCH_HOSTEDOBJS) \

OBJS=\
$(FREEOBJS) \
$(HOSTEDOBJS) \


LIBK_OBJS=$(FREEOBJS:.o=.libk.o)

#BINARIES=libc.a libk.a # Not ready for libc yet.
BINARIES=$(OBJDIR)/libk.a

.PHONY: all clean install install-headers install-libs
.SUFFIXES: .o .libk.o .c .S

all: $(BINARIES)

$(OBJDIR)/libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(OBJDIR)/libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $(abspath $<) -o $@ $(CFLAGS) $(CPPFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -MD -c $(abspath $<) -o $@ $(CPPFLAGS) $(CXXFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.S
	@mkdir -p $(dir $@)
	$(CC) -MD -c $(abspath $<) -o $@ $(CFLAGS) $(CPPFLAGS)

$(OBJDIR)/%.libk.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -MD -c $(abspath $<) -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

$(OBJDIR)/%.libk.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -MD -c $(abspath $<) -o $@ $(LIBK_CPPFLAGS) $(LIBK_CXXFLAGS)


$(OBJDIR)/%.libk.o: $(SRCDIR)/%.S
	$(CC) -MD -c $(abspath $<) -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f $(BINARIES) *.a
	rm -f $(OBJS) $(LIBK_OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) $(LIBK_OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-libs

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-libs: $(BINARIES)
	mkdir -p $(DESTDIR)$(LIBDIR)
	cp $(BINARIES) $(DESTDIR)$(LIBDIR)

-include $(OBJS:.o=.d)
-include $(LIBK_OBJS:.o=.d)
