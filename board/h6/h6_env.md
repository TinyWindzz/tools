### 环境准备

```
atf:
make CROSS_COMPILE=aarch64-linux-gnu- PLAT=sun50i_h6 DEBUG=1 bl31

uboot:
export BL31=/path/to/bl31.bin
make orangepi_one_plus_defconfig && make -j5 CROSS_COMPILE=aarch64-linux-gnu-
dd if=u-boot-sunxi-with-spl.bin of=/dev/sdb bs=8k seek=1
```

### 串口软件使用方法：

```shell
picocom -b 115200 /dev/ttyUSB0
```

### 启动xen uboot命令：

```shell
setenv kernel_addr_r  0x40080000
setenv fdt_addr       0x44000000
setenv xen_addr_r     0x45000000
ext4load mmc 0 ${kernel_addr_r} orangepi3/Image;
ext4load mmc 0 ${fdt_addr} orangepi3/sun50i-h6-orangepi-3.dtb;
ext4load mmc 0 ${xen_addr_r} orangepi3/xen.efi;

fdt addr ${fdt_addr} 0x40000
fdt resize
fdt chosen
fdt set /chosen \#address-cells <1>
fdt set /chosen \#size-cells <1>
fdt mknod /chosen module@0
fdt set /chosen/module@0 compatible "xen,linux-zimage" "xen,multiboot-module"
fdt set /chosen/module@0 reg <${kernel_addr_r} 0x02000000>
fdt set /chosen/module@0 bootargs "console=hvc0 ro root=/dev/mmcblk0p1 rootwait clk_ignore_unused"

setenv bootargs "console=dtuart dtuart=/soc/serial@5000000 root=/dev/mmcblk0p1 rootwait dom0_mem=128M"
booti ${xen_addr_r} - ${fdt_addr}

PS:
CONFIG_EARLY_PRINTK=8250,0x05000000,2 #debug xen
y6F-1JA=c]o3fnhG #密码
```

### 启动内核 uboot 命令：

```shell
ext4load mmc 0 0x40080000 orangepi3/Image;
ext4load mmc 0 0x44000000 orangepi3/sun50i-h6-orangepi-3.dtb;
setenv bootargs = "earlycon=uart8250,mmio32,0x05000000 root=/dev/mmcblk0p1 console=ttyS0,115200n8 loglevel=8 rootwait"
booti 0x40080000 - 0x44000000

#重新挂载ubuntu
mount -o rw,remount /dev/mmcblk0p1

#qemu模拟a53
qemu-system-aarch64 -machine virt -M virt -cpu cortex-a53 -nographic -smp 1 -m 256 -kernel ./Image  -hda ./rootfs.img -append "console=ttyAMA0 root=/dev/vda rw"

#qemu模拟a57
qemu-system-aarch64 -machine virt -M virt,gic_version=3 -cpu cortex-a57 -nographic -smp 2 -m 256 -kernel ./Image  -hda ./rootfs.img -append "console=ttyAMA0 root=/dev/vda rw"

#启动kvm加速
qemu-system-aarch64 -machine virt -M virt,accel=kvm -cpu cortex-a53 -nographic -smp 1 -m 256 -kernel ./Image  -hda ./rootfs.img -append "console=ttyAMA0 root=/dev/vda rw"

#退出qemu
crtl a + x
```

### 内核使用hdmi:

```shell
#driver/media/cec/
insmod cec.ko
#driver/gpu/drm/
insmod drm_panel_orientation_quirks.ko
insmod drm.ko
insmod drm_kms_helper.ko
#driver/gpu/drm/sun4i/
insmod sun4i-drm-hdmi.ko
#driver/gpu/drm/brige/synopsys/
insmod dw-hdmi.ko
#driver/gpu/drm/sun4i/
insmod sun8i_tcon_top.ko
insmod sun4i-tcon.ko
insmod sun4i-frontend.ko
insmod sun4i-drm.ko
insmod sun8i-drm-hdmi.ko
insmod sun8i-mixer.ko
```
