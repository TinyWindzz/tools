

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

