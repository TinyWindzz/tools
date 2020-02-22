# 基于QEMU搭建虚拟化实验环境

```shell
#编译XEN
make -j8 dist-xen XEN_TARGET_ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-

#获取ubuntu rottfs
wget https://cloud-images.ubuntu.com/bionic/current/bionic-server-cloudimg-arm64.img
重命名为ubuntu.qcow2

qemu-system-aarch64 \
   -M virt,gic_version=3,virtualization=true,type=virt \
   -cpu cortex-a57 -nographic -smp 4 -m 8800 \
   -kernel Image.gz --append "console=ttyAMA0 root=/dev/vda1 init=/bin/sh" \
   -drive if=none,file=ubuntu.qcow2,format=qcow2,id=hd0 -device virtio-blk-device,drive=hd0 \
   -netdev user,id=hostnet0,hostfwd=tcp::2222-:22 -device virtio-net-device,netdev=hostnet0

#编译qemu
wget https://download.qemu.org/qemu-4.1.0.tar.xz 
./configure --target-list=aarch64-softmmu 或 ./configure --target-list=arm-softmmu
```

https://cloud.tencent.com/developer/article/1493252

```shell
host:
#在host端首先建立一个bridge设备 br0
brctl addbr br0
#新增网口 tap0
tunctl
#把网口插在交换机上
brctl addif br0 tap0
#使能网口和交换机
ip link set br0 up
ip link set tap0 up
#给交换机设备一个ip地址
ifconfig br0 192.168.88.1
#打开host上的ip转发功能.
#这是为了让桥设备收到数据包之后，根据数据包中的目标ip地址查找host中的路由表进行数据包转发。
echo 1 > /proc/sys/net/ipv4/ip_forward
#设置nat （eth0连接外网）
#这个的意思是br0设备或者其它网卡转发数据包从ens33网口出去的时候更改数据包中的源ip地址（改成eth0的ip地址）
iptables -t nat -A POSTROUTING -o ens33 -j MASQUERADE

#remmove tap bridge
ifconfig tap0 down
tunctl -d tap0
brctl delif br0 tap0
ifconfig br0 down
brctl stp br0 off
brctl delbr br0

qemu:
-device virtio-net-device,netdev=qemunet0,mac=E0:FE:D0:3C:2E:EE -netdev tap,id=qemunet0,ifname=tap0,script=no,downscript=no

guest:
#同时设置默认网关为bridge设备的ip地址
#这个时候当guest端访问外网时，数据包会转发到bridge设备
#由于host端打开了ip转发功能，会把数据包转发到eth0,从而可以访问外网
#guest端设备ip地址保证跟bridge设备在同一个网段
ifconfig eth0 192.168.88.12
route add default gw 192.168.88.1

#开启virtualization选项
qemu-system-aarch64 -machine virt -M virt,gic_version=3,virtualization=true,type=virt -cpu cortex-a57 -nographic -smp 4 -m 1024 -kernel ./Image  -hda ./rootfs.img -append "console=ttyAMA0 root=/dev/vda rw" -device virtio-net-device,netdev=qemunet0,mac=E0:FE:D0:3C:2E:EE -netdev tap,id=qemunet0,ifname=tap0,script=no,downscript=no

#开启kvm选项
qemu-system-aarch64 -machine virt -M virt,gic_version=3,accel=kvm -cpu cortex-a57 -nographic -smp 2 -m 256 -kernel ./Image  -hda ./rootfs.img -append "console=ttyAMA0 root=/dev/vda rw"

#退出qemu
crtl a + x
kill -9 $(ps -a | grep qemu | awk '{print $1}')
```



```shell
#ubuntu开机速度优化
systemd-analyze blame

systemctl disable xxx.service
```

