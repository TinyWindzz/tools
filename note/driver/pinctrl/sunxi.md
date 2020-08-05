配置pin功能的函数
```c
static const struct pinconf_ops sunxi_pconf_ops = {
	.is_generic		= true,
	.pin_config_get		= sunxi_pconf_get,	//用来dump信息
	.pin_config_set		= sunxi_pconf_set,
	.pin_config_group_get	= sunxi_pconf_group_get,	//back to pin_config_get
	.pin_config_group_set	= sunxi_pconf_group_set,	//back to pin_config_set
};

//sunxi_pconf_set中循环设置某个pin的上下拉、驱动强度、power source(待实现)，
//设置power source的时候需要怎么正确操作，怎么把那么多个寄存器放进去。

struct sunxi_pinctrl_group {
	const char	*name;
	unsigned	pin;
};
//我们目前一个group一个pin

enum pin_config_param {
	PIN_CONFIG_BIAS_BUS_HOLD,
	PIN_CONFIG_BIAS_DISABLE,
	PIN_CONFIG_BIAS_HIGH_IMPEDANCE,
	PIN_CONFIG_BIAS_PULL_DOWN,
	PIN_CONFIG_BIAS_PULL_PIN_DEFAULT,
	PIN_CONFIG_BIAS_PULL_UP,
	PIN_CONFIG_DRIVE_OPEN_DRAIN,
	PIN_CONFIG_DRIVE_OPEN_SOURCE,
	PIN_CONFIG_DRIVE_PUSH_PULL,
	PIN_CONFIG_DRIVE_STRENGTH,
	PIN_CONFIG_DRIVE_STRENGTH_UA,
	PIN_CONFIG_INPUT_DEBOUNCE,
	PIN_CONFIG_INPUT_ENABLE,
	PIN_CONFIG_INPUT_SCHMITT,
	PIN_CONFIG_INPUT_SCHMITT_ENABLE,
	PIN_CONFIG_LOW_POWER_MODE,
	PIN_CONFIG_OUTPUT_ENABLE,
	PIN_CONFIG_OUTPUT,
	PIN_CONFIG_POWER_SOURCE,
	PIN_CONFIG_SLEEP_HARDWARE_STATE,
	PIN_CONFIG_SLEW_RATE,
	PIN_CONFIG_SKEW_DELAY,
	PIN_CONFIG_PERSIST_STATE,
	PIN_CONFIG_END = 0x7F,
	PIN_CONFIG_MAX = 0xFF,
};

增加power-source可以参考drivers/soc/tegra/pmc.c。
```

````c
static const struct pinctrl_ops sunxi_pctrl_ops = {
	.dt_node_to_map		= sunxi_pctrl_dt_node_to_map,
	.dt_free_map		= sunxi_pctrl_dt_free_map,
	.get_groups_count	= sunxi_pctrl_get_groups_count,
	.get_group_name		= sunxi_pctrl_get_group_name,
	.get_group_pins		= sunxi_pctrl_get_group_pins,
};
````

```c
static const struct pinmux_ops sunxi_pmx_ops = {
	.get_functions_count	= sunxi_pmx_get_funcs_cnt,
	.get_function_name	= sunxi_pmx_get_func_name,
	.get_function_groups	= sunxi_pmx_get_func_groups,
	.set_mux		= sunxi_pmx_set_mux,
	.gpio_set_direction	= sunxi_pmx_gpio_set_direction,
	.request		= sunxi_pmx_request,
	.free			= sunxi_pmx_free,
	.strict			= true,
};
```

有哪些地方要设置、更新寄存器，受到偏移更改影响？