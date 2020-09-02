#!/bin/bash

ROOTFS=rootfs.cpio.gz
ROOTFSOUT=rfout

extract_rootfs()
{
        mkdir $ROOTFSOUT
        gzip -dc $ROOTFS | (cd $ROOTFSOUT; fakeroot cpio -i)
}

generate_rootfs()
{
        cd $ROOTFSOUT
        find . | fakeroot cpio -o -Hnewc | gzip > ../"$ROOTFS"
        rm -rf ../$ROOTFSOUT
}

case $1 in
"e")
        extract_rootfs
        ;;
"g")
        generate_rootfs
        ;;
esac
