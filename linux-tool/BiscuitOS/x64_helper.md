BiscuitOS linux-5.0-x86_64 Usermanual
--------------------------------

> - [Build Linux Kernel](#A0)
>
> - [Build Busybox](#A1)
>
> - [Re-Build Rootfs](#A2)
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
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-x86_64/linux/linux
make ARCH=x86_64 clean
make ARCH=x86_64 x86_64_defconfig
make ARCH=x86_64 menuconfig

  General setup --->
        [*]Initial RAM filesystem and RAM disk (initramfs/initrd) support

  Device Driver --->
        [*] Block devices --->
              <*> RAM block device support
              (153600) Default RAM disk size

make ARCH=x86_64 bzImage -j4
make ARCH=x86_64 modules -j4
sudo make ARCH=x86_64 INSTALL_MOD_PATH=/home/frank/Desktop/BiscuitOS/output/linux-5.0-x86_64/rootfs/rootfs/ modules_install
```

---------------------------------
<span id="A1"></span>

## Build Busybox

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-x86_64/busybox/busybox
make clean
make menuconfig

  Busybox Settings --->
    Build Options --->
      [*] Build BusyBox as a static binary (no shared libs)

make -j4
make install
```
---------------------------------
<span id="A2"></span>

## Re-Build Rootfs

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-x86_64
./RunBiscuitOS.sh pack
```
---------------------------------
<span id="A5"></span>

## Running BiscuitOS

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-x86_64
./RunBiscuitOS.sh
```

If you want exit from BiscuitOS, pls use: Ctrl-A + X


---------------------------------

## Running BiscuitOS with NetWorking

```
cd /home/frank/Desktop/BiscuitOS/output/linux-5.0-x86_64
./RunBiscuitOS.sh net
```

