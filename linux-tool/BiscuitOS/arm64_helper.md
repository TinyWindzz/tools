BiscuitOS linux-5.0-aarch Usermanual
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

---------------------------------
<span id="A0"></span>

## Build Linux Kernel

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/linux/linux
make ARCH=arm64 clean
make ARCH=arm64 defconfig
make ARCH=arm64 menuconfig


  [*] Enable loadable module support  --->


make ARCH=arm64 CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/aarch64-linux-gnu/aarch64-linux-gnu/bin/aarch64-linux-gnu- Image -j4
make ARCH=arm64 CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/aarch64-linux-gnu/aarch64-linux-gnu/bin/aarch64-linux-gnu- modules -j4
make ARCH=arm64 INSTALL_MOD_PATH=/home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/rootfs/rootfs/ modules_install
```

---------------------------------
<span id="A1"></span>

## Build Busybox

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/busybox/busybox
make clean
make menuconfig

  Busybox Settings --->
    Build Options --->
      [*] Build BusyBox as a static binary (no shared libs)

make CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/aarch64-linux-gnu/aarch64-linux-gnu/bin/aarch64-linux-gnu- -j4

make CROSS_COMPILE=/home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/aarch64-linux-gnu/aarch64-linux-gnu/bin/aarch64-linux-gnu- install
```
---------------------------------
<span id="A2"></span>

## Re-Build Rootfs

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch
./RunBiscuitOS.sh pack
```
---------------------------------
<span id="A3"></span>

## Mount a Freeze Disk

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch
./RunBiscuitOS.sh mount
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/FreezeDir
```

---------------------------------
<span id="A4"></span>

## Un-mount a Freeze Disk

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch
./RunBiscuitOS.sh umount
```

---------------------------------
<span id="A5"></span>

## Running BiscuitOS

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch
./RunBiscuitOS.sh
```

If you want exit from BiscuitOS, pls use: Ctrl-A + X


---------------------------------

## Running BiscuitOS with NetWorking

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch
./RunBiscuitOS.sh net
```

---------------------------------
<span id="A6"></span>

## Debuging BiscuitOS

```
> First Terminal

cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch
./RunBiscuitOS.sh debug

> Second Terminal

/home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/aarch64-linux-gnu/aarch64-linux-gnu/bin/aarch64-linux-gnu-gdb /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/linux/linux/vmlinux

(gdb) target remote :1234
(gdb) b start_kernel
(gdb) c
```

