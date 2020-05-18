#!/bin/bash
SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export TOOLCHAIN_BINDIR=${HOME}/opt/cross/bin

# Add path to our cross compiler.
export PATH=${PATH}:${TOOLCHAIN_BINDIR}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-gcc
export CXX=${HOST}-g++
export GDB=${HOST}-gdb

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-std=gnu11'
export CPPFLAGS='-O2 -g -Wall -Wextra'
export CXXFLAGS='-std=c++17 -fno-exceptions -fno-rtti'

# This file dir:
export SCRIPT_DIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
export BUILDDIR="$SCRIPT_DIR/_build"
export OBJDIR="$BUILDDIR/intermediate"
export TARGETDIR="$BUILDDIR/target"

# Create some links to the tool chain
export HOST_BINDIR=$SCRIPT_DIR/_build/host/bin
mkdir -p $HOST_BINDIR
ln -sf $TOOLCHAIN_BINDIR/$CXX $HOST_BINDIR/g++
ln -sf $TOOLCHAIN_BINDIR/$GDB $HOST_BINDIR/gdb
ln -sf $TOOLCHAIN_BINDIR/$CC $HOST_BINDIR/gcc
ln -sf $TOOLCHAIN_BINDIR/$AR $HOST_BINDIR/ar
ln -sf $TOOLCHAIN_BINDIR/$AS $HOST_BINDIR/as

# Configure the cross-compiler to use the desired system root.
export SYSROOT="$TARGETDIR/sysroot"
export CC="$CC --sysroot=$SYSROOT"
export CXX="$CXX --sysroot=$SYSROOT"

# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
  export CXX="$CXX -isystem=$INCLUDEDIR"
fi

