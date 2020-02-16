dd if=/dev/zero of=rootfs.img bs=1M count=4k oflag=direct
mkfs.ext4 rootfs.img
mkdir mount
mount rootfs.img mount
cp -rfp arm64_1.30.1_static/* mount/
umount mount
rmdir mount
e2fsck -p -f rootfs.img
