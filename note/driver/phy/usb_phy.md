如何检测usb插入、u盘插入

OTG 检测的原理是:
　　USB OTG标准在完全兼容USB2.0标准的基础上，增添了[电源管理](http://www.hqchip.com/app/859)（节省功耗）功能，它允许设备既可作为主机，也可作为外设操作（两用OTG）。USB OTG技术可实现没有主机时设备与设备之间的数据[传输](http://www.elecfans.com/tags/数据传输/)。例如：数码相机可以直接与[打印机](http://www.elecfans.com/tags/打印机/)连接并打印照片，[手机](http://bbs.elecfans.com/zhuti_tel_1.html)与手机之间可以直接传送数据等，从而拓展了USB技术的应用范围。在OTG中，初始主机设备称为A设备，外设称为B设备。也就是说，手机既可以做外设，又可以做主机来传送数据，可用[电缆](http://www.hqchip.com/app/862)的连接方式来决定初始角色(由ID线的状态来决定)。

USB OTG[接口](http://www.hqchip.com/app/1039)中有5条线：

2条用来传送数据（D+ 、D-）;

1条是[电源](http://bbs.elecfans.com/zhuti_power_1.html)线(VBUS);

1条则是接地线(GND)、

1条是ID线。ID线---以用于识别不同的电缆端点，mini-A插头(即A外设)中的ID引脚接地，mini-B插头（即B外设）中的ID引脚浮空。当OTG设备检测到接地的ID引脚时，表示默认的是A设备（主机），而检测到ID引脚浮空的设备则认为是B设备（外设）。

只有而言支持USB OTG的设备（即可以做USB Host有可以做Slave的设备），USB_ID信号才有意义。
当设备检测到USB_ID信号为低时，表该设备应作为Host（主机，也称A设备）用。
当设备检测到USB_ID信号为高时，表示该设备作为Slave(外设，也称B设备）用。

实际的USB连接线中，是没有USB_ID这根线的。 都是在接口部分直接拉死的的。
对于Host端，只需将连接线的USB_ID pin和地短接即可，
对于Slave端，USB连接线的USB_ID pin是悬空的。（设备内部上拉）。



dts:

```c
    phy@5100400 {
        #phy-cells = <1>;
        compatible = "allwinner,sun50i-h6-usb-phy";
        reg = <0x05100400 0x24>,
              <0x05101800 0x4>,
              <0x05311800 0x4>;
        reg-names = "phy_ctrl",
                    "pmu0",
                    "pmu3";
        clocks = <&ccu CLK_USB_PHY0>,
                 <&ccu CLK_USB_PHY3>;
        clock-names = "usb0_phy",
                      "usb3_phy";
        resets = <&ccu RST_USB_PHY0>,
                 <&ccu RST_USB_PHY3>;
        reset-names = "usb0_reset",
                      "usb3_reset";
        usb0_id_det-gpios = <&pio 2 6 GPIO_ACTIVE_HIGH>; /* PC6 */
        usb0_vbus-supply = <&reg_vcc5v>;
        usb3_vbus-supply = <&reg_vcc5v>;
    };

对于pmu3配置的是0x800寄存器, BIT(0)、BIT(8)、BIT(9)、BIT(10)
phy_ctrl看不到控制了哪些寄存器

	switch (mode) {
	case PHY_MODE_USB_HOST:
		new_mode = USB_DR_MODE_HOST;
		break;
	case PHY_MODE_USB_DEVICE:
		new_mode = USB_DR_MODE_PERIPHERAL;
		break;
	case PHY_MODE_USB_OTG:
		new_mode = USB_DR_MODE_OTG;
		break;
	default:
		return -EINVAL;
	}

分析一下sun4i_usb_phy0_id_vbus_det_scan这个函数
```

