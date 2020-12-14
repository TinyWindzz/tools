[TOC]

## BiscuitOS on ubuntu20

### 准备工作

https://github.com/BiscuitOS/BiscuitOS

https://biscuitos.github.io/blog/ （需要翻墙）

ubuntu16基础包：

```
sudo apt-get install -y qemu gcc make gdb git figlet
sudo apt-get install -y libncurses5-dev iasl wget
sudo apt-get install -y device-tree-compiler
sudo apt-get install -y flex bison libssl-dev libglib2.0-dev
sudo apt-get install -y libfdt-dev libpixman-1-dev
sudo apt-get install -y python pkg-config u-boot-tools intltool xsltproc
sudo apt-get install -y gperf libglib2.0-dev libgirepository1.0-dev
sudo apt-get install -y gobject-introspection
sudo apt-get install -y python2.7-dev python-dev bridge-utils
sudo apt-get install -y uml-utilities net-tools
sudo apt-get install -y libattr1-dev libcap-dev
sudo apt-get install -y kpartx libsdl2-dev libsdl1.2-dev
sudo apt-get install -y debootstrap bsdtar
sudo apt-get install -y libelf-dev gcc-multilib g++-multilib
sudo apt-get install -y libcap-ng-dev

On 64-Bit Machine:

sudo apt-get install lib32z1 lib32z1-dev libc6:i386
```

ubuntu20额外需要安装：

```
sudo apt install python libglib2.0-dev libpixman-1-dev libcap-dev
sudo apt install libcap-ng-dev flex bison libncurses-dev libssl-dev
```

### 上手

#### linux-5.0 for arm64

ubuntu20需要使用qemu5.x以上版本

```c
diff --git a/configs/linux-5.0-arm64_defconfig b/configs/linux-5.0-arm64_defconfig
index 504b25f..2536467 100644
--- a/configs/linux-5.0-arm64_defconfig
+++ b/configs/linux-5.0-arm64_defconfig
@@ -8,7 +8,7 @@ CONFIG_BUSYBOX_VERSION="1.24.2"
 CONFIG_BUSYBOX_SRC=3
 CONFIG_PK_QEMU_SYSTEM=y
 CONFIG_QEMU_SYSTEM_WGET=y
-CONFIG_QEMU_SYSTEM_VERSION="3.1.0"
+CONFIG_QEMU_SYSTEM_VERSION="5.0.0"
 CONFIG_QEMU_SYSTEM_SRC=3
 CONFIG_ROOTFS=y
 CONFIG_FS_EXT4=y
```

```
make linux-5.0-arm64_defconfig
make

 ____  _                _ _    ___  ____  
| __ )(_)___  ___ _   _(_) |_ / _ \/ ___| 
|  _ \| / __|/ __| | | | | __| | | \___ \ 
| |_) | \__ \ (__| |_| | | |_| |_| |___) |
|____/|_|___/\___|\__,_|_|\__|\___/|____/ 
                                          
***********************************************
Output:
 /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch 

linux:
 /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/linux/linux 

README:
 /home/frank/Desktop/BiscuitOS/output/linux-5.0-aarch/README.md 

Blog:
 https://biscuitos.github.io/blog/BiscuitOS_Catalogue/ 
 
由于未做裁减，需要把root.img改大。把RunBiscuitOS.sh中ROOTFS_SIZE=1024改为合适大小。
```

###  guest 与 host数据互通

```shell
#guest kernel：
CONFIG_NET_9P=y
CONFIG_NET_9P_VIRTIO=y
# CONFIG_NET_9P_DEBUG is not set
CONFIG_9P_FS=y
# CONFIG_9P_FS_POSIX_ACL is not set
# CONFIG_9P_FS_SECURITY is not set

#qemu：
-fsdev local,security_model=passthrough,id=fsdev0,path=/tmp/share
-device virtio-9p-device,id=fs0,fsdev=fsdev0,mount_tag=hostshare

#guest：
mount -t 9p -o trans=virtio,version=9p2000.L hostshare /tmp
```
