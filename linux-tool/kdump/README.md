# crashdump实践（基于kexec）

## 使用qemu实践crashdump

### 部署kexec工具

```
1.http://kernel.org/pub/linux/utils/kernel/kexec/kexec-tools.tar.gz

2.tar xvpzf kexec-tools.tar.gz

3.LDFLAGS=-static ./configure ARCH=arm64 --build=x86_64-linux-gnu --host=aarch64-linux-gnu --target=aarch64-linux-gnu --without-xen

4.make

5.cp build/* rootfs/
```

### 获取vmcore

```
CONFIG_KEXEC=y 、 
CONFIG_SYSFS=y 、 
CONFIG_DEBUG_INFO=y 、 
CONFIG_CRASH_DUMP=y 、 
CONFIG_PROC_VMCORE=y
默认都开了

qemu-system-aarch64 -machine virt -M virt,gic_version=3 -cpu cortex-a57 -nographic -smp 2 -m 512 -kernel /work/h6/mainline/linux/arch/arm64/boot/Image  -hda ./rootfs.img -append "console=ttyAMA0 root=/dev/vda rw crashkernel=128M nr_cpus=2"

kexec -p --command-line="console=ttyAMA0 root=/dev/vda rw nr_cpus=2 nr_cpus=1" orangepi3/Image;
echo c > proc/sysrq-trigger;

cp proc/vmcore .

kill -9 $(ps -a | grep qemu | awk '{print $1}')
```

### 使用crash工具分析

```
https://github.com/crash-utility/crash/releases

编译：
make target=ARM 或 make target=ARM64
（strip -s crash去除编译生成的Crash 中的多余符号）

./crash vmlinux vmcore
```

在5.4的内核由于arm64 52bit内核虚拟地址的支持引入了bug，目前有临时解决方法。

```
来自redhat的Bhupesh Sharma在
https://www.redhat.com/archives/crash-utility/2019-November/msg00014.html中提到了一种修复方法，http://lists.infradead.org/pipermail/kexec/2019-November/023962.html
```

[ 52-bit kernel + user VAs](https://lwn.net/Articles/795654/ ) 

[ 深入学习kdump原理](https://www.jianshu.com/p/1645da328c5e ) 

## Crash 常规调试

| 命令    | 说明                                                         | 例子                                                         |
| ------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| *       | 指针的快捷方式，用于代替struct/union                         | *page 0xc02943c0：显示0xc02943c0地址的page结构体             |
| files   | 显示已打开的所有文件的信息                                   | files 462：显示进程462的已打开文件信息                       |
| mach    | 显示与机器相关的参数信息                                     | mach：显示CPU型号，核数，内存大小等                          |
| sys     | 显示特殊系统的数据                                           | sys config：显示CONFIG_xxx配置宏状态                         |
| timer   | 无参数。按时间的先后顺序显示定时器队列的数据                 | timer：显示详细信息                                          |
| mod     | 显示已加载module的详细信息                                   | mod：列出所有已加载module信息                                |
| runq    | 显示runqueue信息                                             | runq：显示所有runqueue里的task                               |
| tree    | 显示基数树/红黑树结构                                        | tree -t rbtree -o vmap_area.rb_node vmap_area_root：显示所有红黑树vmap_area.rb_node节点地址 |
| fuser   | 显示哪些task使用了指定的文件/socket                          | fuser /usr/lib/libkfm.so.2.0.0：显示使用了该文件的所有进程   |
| mount   | 显示已挂载的文件系统信息                                     | mount：当前已挂载的文件系统信息                              |
| ipcs    | 显示System V IPC信息                                         | ipcs：显示系统中System V IPC信息                             |
| ps      | 显示进程状态                                                 | ps：类似ps命令                                               |
| struct  | 显示结构体的具体内容                                         | struct vm_area_struct c1e44f10：显示c1e44f10结构             |
| union   | 显示联合体的具体内容，用法与struct一致                       | union bdflush_param：显示bdflush_param结构                   |
| waitq   | 列出在等待队列中的所有task。参数可以指定队列的名称、内存地址等 | waitq buffer_wait：显示buffer_wait等待队列信息               |
| irq     | 显示中断编号的所有信息                                       | irq 18：显示中断18的信息                                     |
| list    | 显示链表的内容                                               | list task_struct.p_pptr c169a000：显示c169a000地址所指task里p_pptr链表 |
| log     | 显示内核的日志，以时间的先后顺序排列                         | log -m：显示kernel log                                       |
| dev     | 显示数据关联着的块设备分配，包括端口使用、内存使用及PCI设备数据 | dev：显示字符/块设备相关信息                                 |
| sig     | 显示一个或者多个task的signal-handling数据                    | sig 8970：显示进程8970的信号处理相关信息                     |
| task    | 显示指定内容或者进程的task_struct的内容                      | task -x：显示当前进程task_struct等内容                       |
| swap    | 无参数。显示已配置好的交换设备信息                           | swap：交换设备信息                                           |
| search  | 在给定范围的用户、内核虚拟内存或者物理内存搜索值             | search -u deadbeef：在用户内存搜索0xdeadbeef                 |
| bt      | 显示调用栈信息                                               | bt：显示当前调用栈                                           |
| net     | 显示各种网络相关的数据                                       | net：显示网络设备列表                                        |
| vm      | 显示task的基本虚拟内存信息                                   | vm：类似于/proc/self/maps                                    |
| btop    | 把一个16进制地址转换成它的分页号                             | N/A                                                          |
| ptob    | 该命令与btop相反，是把一个分页号转换成地址                   | N/A                                                          |
| vtop    | 显示用户或内核虚拟内存所对应的物理内存                       | N/A                                                          |
| ptov    | 该命令与vtop相反。把物理内存转换成虚拟内存                   | N/A                                                          |
| pte     | 16进制页表项转换为物理页地址和页的位设置                     | N/A                                                          |
| alias   | 显示或建立一个命令的别名                                     | alias kp kmem -p：以后用kp命令相当于kmem -p                  |
| foreach | 用指定的命令枚举                                             | foreach bt：显示所有进程的调用栈                             |
| repeat  | 循环执行指定命令                                             | repeat -1 p jiffies：每个1s执行p jiffies                     |
| ascii   | 把16进制表示的字符串转化成ascii表示的字符串                  | ascii 62696c2f7273752f：结果为/usr/lib                       |
| set     | 设置要显示的内容，内容一般以进程为单位，也可以设置当前crash的内部变量 | set -p：切换到崩溃进程的上下文环境                           |
| p       | print的缩写，打印表达式的值。表达式可以为变量，也可以为结构体 | N/A                                                          |
| dis     | disassemble的缩写。把一个命令或者函数分解成汇编代码          | dis sys_signal：反汇编sys_signal函数                         |
| whatis  | 搜索数据或者类型的信息                                       | whatis linux_binfmt：显示linux_binfmt结构体                  |
| eval    | 计算表达式的值，及把计算结果或者值显示为16、10、8和2进制     | N/A                                                          |
| kmem    | 显示当前kernel使用内存状况                                   | kmem -i：显示kernel使用内存状况                              |
| sym     | 显示符号所在的虚拟地址，或虚拟地址对应的符号                 | sym jiffies：显示jiffies地址                                 |
| rd      | 显示指定内存的内容。缺少的输出格式是十六进制输出             | rd -a linux_banner：显示linux_banner内容                     |
| wr      | 根据参数指定的写内存。在定位系统出错的地方时，一般不使用该命令 wr | my_debug_flag 1：修改my_debug_flag值为1                      |
| gdb     | 执行GDB原生命令                                              | gdb help：执行gdb的help命令                                  |
| extend  | 动态装载或卸载crash额外的动态链接库                          | N/A                                                          |
| q       | 退出                                                         | N/A                                                          |
| exit    | 同q，退出                                                    | N/A                                                          |
| help    | 帮助命令                                                     | N/A                                                          |
