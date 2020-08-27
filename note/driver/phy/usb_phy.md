如何检测usb插入、u盘插入

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
```

