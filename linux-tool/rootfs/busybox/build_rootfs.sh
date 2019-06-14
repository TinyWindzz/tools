mkdir -p etc/init.d dev sys proc tmp mnt

echo '/bin/mount -a
mkdir -p /dev/pts
mount -t devpts devpts /dev/pts
echo /sbin/mdev > /proc/sys/kernel/hotplug
mdev -s
mount -o remount rw /' > etc/init.d/rcS

chmod a+x etc/init.d/rcS

echo 'proc /proc proc defaults 0 0
tmpfs /tmp tmpfs defaults 0 0
sysfs /sys sysfs defaults 0 0
tmpfs /dev tmpfs defaults 0 0
debugfs /sys/kernel/debug debugfs defaults 0 0' > etc/fstab

echo '::sysinit:/etc/init.d/rcS
::respawn:-/bin/sh
::askfirst:-/bin/sh
::ctrlaltdel:/bin/umount -a -r' > etc/inittab

mknod dev/console c 5 1
mknod dev/null c 1 3
