

```c
		usb2otg: usb@5100000 {
			compatible = "allwinner,sun50i-h6-musb",
				     "allwinner,sun8i-a33-musb";
			reg = <0x05100000 0x0400>;
			clocks = <&ccu CLK_BUS_OTG>;
			resets = <&ccu RST_BUS_OTG>;
			interrupts = <GIC_SPI 23 IRQ_TYPE_LEVEL_HIGH>;
			interrupt-names = "mc";
			phys = <&usb2phy 0>;
			phy-names = "usb";
			extcon = <&usb2phy 0>;
			status = "disabled";
		};

		ehci0: usb@5101000 {
			compatible = "allwinner,sun50i-h6-ehci", "generic-ehci";
			reg = <0x05101000 0x100>;
			interrupts = <GIC_SPI 24 IRQ_TYPE_LEVEL_HIGH>;
			clocks = <&ccu CLK_BUS_OHCI0>,
				 <&ccu CLK_BUS_EHCI0>,
				 <&ccu CLK_USB_OHCI0>;
			resets = <&ccu RST_BUS_OHCI0>,
				 <&ccu RST_BUS_EHCI0>;
			status = "disabled";
		};

		ohci0: usb@5101400 {
			compatible = "allwinner,sun50i-h6-ohci", "generic-ohci";
			reg = <0x05101400 0x100>;
			interrupts = <GIC_SPI 25 IRQ_TYPE_LEVEL_HIGH>;
			clocks = <&ccu CLK_BUS_OHCI0>,
				 <&ccu CLK_USB_OHCI0>;
			resets = <&ccu RST_BUS_OHCI0>;
			status = "disabled";
		};
```
将otg配置成mass存储脚本

```shell
#!/bin/sh
# config mass_storage functions

dd if=/dev/zero of=/dev/a.bin bs=1M count=100

mount -t configfs none /sys/kernel/config
mkdir /sys/kernel/config/usb_gadget/g1
echo "0x18d1" > /sys/kernel/config/usb_gadget/g1/idVendor
echo "0x0001" > /sys/kernel/config/usb_gadget/g1/idProduct
mkdir /sys/kernel/config/usb_gadget/g1/strings/0x409
mkdir /sys/kernel/config/usb_gadget/g1/functions/mass_storage.usb0
echo /dev/a.bin > /sys/kernel/config/usb_gadget/g1/functions/mass_storage.usb0/lun.0/file
mkdir /sys/kernel/config/usb_gadget/g1/configs/c.1
echo 0xc0 > /sys/kernel/config/usb_gadget/g1/configs/c.1/bmAttributes
echo 500 > /sys/kernel/config/usb_gadget/g1/configs/c.1/MaxPower
mkdir /sys/kernel/config/usb_gadget/g1/configs/c.1/strings/0x409
ln -s /sys/kernel/config/usb_gadget/g1/functions/mass_storage.usb0/ /sys/kernel/config/usb_gadget/g1/configs/c.1/

# enable udc
udc=`ls /sys/class/udc`
echo $udc > /sys/kernel/config/usb_gadget/g1/UDC
```

