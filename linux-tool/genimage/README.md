```shell
#download genimage
https://github.com/pengutronix/genimage
apt install autoreconf libconfuse-dev
./autogen.sh
./configure CFLAGS='-g -O0' --prefix=/usr
make

#mkimage
mkdir root tmp;
./genimage/genimage --config genimage.cfg --inputpath ./  ;
rmdir root tmp;

#烧写 etcher: https://www.balena.io/etcher/
time dd if=images/sdcard.img of=/dev/sdb

#调整分区大小
parted /dev/sdb
#Change display unit to sectors: unit s
(parted) p
(parted) rm 1
(parted) mkpart primary 1049kB -1
(parted) p
(parted) q
e2fsck -f /dev/sdb1
resize2fs /dev/sdb1
```

genimage.cfg

```
image sdcard.img {
        hdimage {
        }   

        partition boot {
                in-partition-table = "no"
                image = "u-boot-sunxi-with-spl.bin"
                offset = 8192
                size = 1040384 # 1MB - 8192
        }   

        partition rootfs {
                partition-type = 0x83
                image = "rootfs.ext4"
        }   
}
```
