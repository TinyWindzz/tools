```shell
#download genimage
https://github.com/pengutronix/genimage
apt install autoreconf libconfuse-dev
./autogen.sh
./configure CFLAGS='-g -O0' --prefix=/usr
make

#mkimage
mkdir root tmp
./genimage/genimage --config genimage.cfg --inputpath ./
rmdir root tmp

#dd
time dd if=images/sdcard.img of=/dev/sdb
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

