#!/bin/bash
set -e
. ./config.sh

args="-s -S"

qemu-system-$(./target-triplet-to-arch.sh $HOST) $args -cdrom cozyos.iso & ${GDB} -ex "target remote localhost:1234" -ex "symbol-file ${OBJDIR}/cozyos.kernel"
