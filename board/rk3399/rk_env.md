### 环境准备

#### Compile U-Boot

```
=> make nanopi-neo4-rk3399_defconfig
=> make CROSS_COMPILE=aarch64-linux-gnu- -j10
```

#### Get the rkbin

```
git clone https://github.com/rockchip-linux/rkbin.git
```

#### Create trust.img

```
=> cd ../rkbin
=> ./tools/trust_merger RKTRUST/RK3399TRUST.ini
```

#### Create uboot.img

```
=> cd ../rkbin
=> ./tools/loaderimage --pack --uboot ../u-boot/u-boot-dtb.bin uboot.img

(Get trust.img and uboot.img, copy to uboot)
```

#### Create idbloader.img

```
=> cd ../u-boot
=> ./tools/mkimage  -n rk3399 -T rksd -d  ../rkbin/bin/rk33/rk3399_ddr_800MHz_v1.24.bin idbloader.img
=> cat ../rkbin/bin/rk33/rk3399_miniloader_v1.24.bin >> idbloader.img
```

#### dd

```
mmc or sdcard is ok!

dd if=idbloader.img of=/dev/sdb seek=64
dd if=trust.img of=/dev/sdb seek=24576
dd if=uboot.img of=/dev/sdb seek=16384

First sector (2048-62914559, default 2048): 80960
Last sector, +sectors or +size{K,M,G,T,P} (80960-62914559, default 62914559):
制作分区的时候，注意留这个空间！！！
```

### boot kernel

```
You can use picocom:
picocom -b 1500000 /dev/ttyUSB0

#for sdcard: mmcblk1p1
ext4load mmc 1 0x02080000 nanopi-neo4/Image;
ext4load mmc 1 0x01f00000 nanopi-neo4/rk3399-nanopi-neo4.dtb;
setenv bootargs "earlyprintk swiotlb=1 root=/dev/mmcblk1p1 rw rootwait"
booti 0x02080000 - 0x01f00000

#for mmc: mmcblk2p1
ext4load mmc 0 0x02080000 nanopi-neo4/Image;
ext4load mmc 0 0x01f00000 nanopi-neo4/rk3399-nanopi-neo4.dtb;
setenv bootargs "earlyprintk swiotlb=1 root=/dev/mmcblk2p1 rw rootwait"
booti 0x02080000 - 0x01f00000
```

doc/README.rockchip