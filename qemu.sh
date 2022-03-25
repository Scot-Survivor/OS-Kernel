#!/bin/sh
set -e
. ./config.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel ./cmake-build-debug-i686/MyOS.kernel -S -s