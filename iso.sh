#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/cozyos.kernel isodir/boot/cozyos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "cozyos" {
	multiboot /boot/cozyos.kernel
}
EOF
grub-mkrescue -o cozyos.iso isodir
