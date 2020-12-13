BiscuitOS linux-5.8-arm32 Usermanual
--------------------------------

> - [Build Linux Kernel](#A0)
>
> - [Build Busybox](#A1)
>
> - [Re-Build Rootfs](#A2)
>
> - [Mount a Freeze Disk](#A3)
>
> - [Un-mount a Freeze Disk](#A4)
>
> - [Running BiscuitOS](#A5)
>
> - [Debugging BiscuitOS](#A6)
>
> - [Running BiscuitOS with NetWorking](#A7)

## Build Linux Kernel

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/linux/linux
make ARCH=arm clean
make ARCH=arm vexpress_defconfig
make ARCH=arm menuconfig

  Enable the block layer --->
        [*] Support for large (2TB+) block devices and files

make ARCH=arm CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi- -j4
make ARCH=arm CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi- modules -j4
sudo make ARCH=arm INSTALL_MOD_PATH=/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/rootfs/rootfs/ modules_install
```

## Build Busybox

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/busybox/busybox
make clean
make menuconfig

  Busybox Settings --->
    Build Options --->
      [*] Build BusyBox as a static binary (no shared libs)

make CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi- -j4

make CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi- install
```
## Re-Build Rootfs

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh pack
```
## Mount a Freeze Disk

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh mount
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/FreezeDir
```

## Un-mount a Freeze Disk

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh umount
```

## Running BiscuitOS

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh
```

If you want exit from BiscuitOS, pls use: Ctrl-A + X


---------------------------------

## Running BiscuitOS with NetWorking

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh net
```

## Debuging BiscuitOS

> - [Debugging zImage before Relocated](#B0)
>
> - [Debugging zImage After Relocated](#B1)
>
> - [Debugging kernel MMU OFF before start_kernel](#B2)
>
> - [Debugging kernel MMU ON before start_kernel](#B3)
>
> - [Debugging kernel after start_kernel](#B4)

#### Debugging zImage before Relocated

```
> First Terminal

cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh debug

> Second Terminal

/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi-gdb -x /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/package/gdb/gdb_zImage

(gdb) b XXX_bk
(gdb) c
(gdb) info reg
```

#### Debugging zImage After Relocated

```
> First Terminal

cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh debug

> Second Terminal

/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi-gdb -x /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/package/gdb/gdb_RzImage

(gdb) b XXX_bk
(gdb) c
(gdb) info reg
```

#### Debugging kernel MMU OFF before start_kernel

```
> First Terminal

cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh debug

> Second Terminal

/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi-gdb -x /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/package/gdb/gdb_Image

(gdb) b XXX_bk
(gdb) c
(gdb) info reg
```

#### Debugging kernel MMU ON before start_kernel

```
> First Terminal

cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh debug

> Second Terminal

/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi-gdb -x /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/package/gdb/gdb_RImage

(gdb) b XXX_bk
(gdb) c
(gdb) info reg

```

#### Debugging kernel after start_kernel

```
> First Terminal

cd /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32
./RunBiscuitOS.sh debug

> Second Terminal

/home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/arm-linux-gnueabi/arm-linux-gnueabi/bin/arm-linux-gnueabi-gdb /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/linux/linux/vmlinux -x /home/frank/Desktop/BiscuitOS/output/linux-5.8-arm32/package/gdb/gdb_Kernel

(gdb) b XXX_bk
(gdb) c
(gdb) info reg
```

