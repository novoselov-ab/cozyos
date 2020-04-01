#!/bin/sh
set -e
. ./build.sh

mkdir -p _build/isodir
mkdir -p _build/isodir/boot
mkdir -p _build/isodir/boot/grub

cp _build/target/sysroot/boot/cozyos.kernel _build/isodir/boot/cozyos.kernel
cat > _build/isodir/boot/grub/grub.cfg << EOF
menuentry "cozyos" {
	multiboot /boot/cozyos.kernel
}
EOF
grub-mkrescue -o cozyos.iso _build/isodir
