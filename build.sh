#!/bin/sh

set -e

echo "Building..."

tup

echo "Installing Boot Sector..."

dd if=./dist/boot/boot-sector.bin of=./disk.bin conv=notrunc

echo "Installing Stage Two..."

dd if=./dist/boot/mbr-break.bin of=./disk.bin conv=notrunc seek=1

echo "Creating FS..."

tar cfv dist.tar ./dist/

echo "Installing FS..."

dd if=./dist.tar of=./disk.bin conv=notrunc seek=32

rm dist.tar

bochs -f ./bochs.conf -q
