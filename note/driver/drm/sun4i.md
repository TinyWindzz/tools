[TOC]

## 主要代码

```shell
#去掉hdmi和老的支持
sun4i-drm-y                     += sun4i_drv.o
sun4i-drm-y                     += sun4i_framebuffer.o

sun8i-mixer-y                   += sun8i_mixer.o sun8i_ui_layer.o \
                                ¦  sun8i_vi_layer.o sun8i_ui_scaler.o \
                                ¦  sun8i_vi_scaler.o sun8i_csc.o

sun4i-tcon-y                    += sun4i_crtc.o
sun4i-tcon-y                    += sun4i_dotclock.o
sun4i-tcon-y                    += sun4i_lvds.o
sun4i-tcon-y                    += sun4i_tcon.o
sun4i-tcon-y                    += sun4i_rgb.o

obj-$(CONFIG_DRM_SUN4I)         += sun4i-drm.o
obj-$(CONFIG_DRM_SUN4I)         += sun4i-tcon.o
obj-$(CONFIG_DRM_SUN4I)         += sun4i_tv.o
obj-$(CONFIG_DRM_SUN4I)         += sun6i_drc.o

obj-$(CONFIG_DRM_SUN6I_DSI)     += sun6i_mipi_dsi.o
obj-$(CONFIG_DRM_SUN8I_MIXER)   += sun8i-mixer.o
obj-$(CONFIG_DRM_SUN8I_TCON_TOP) += sun8i_tcon_top.o
```
## 主要组件

### sun8i mixer

#### sun8i ui

sun8i_ui_layer_atomic_update

#### sun8i vi

sun8i_vi_layer_atomic_update

### sun4i tcon top

export hdmi源、de源选择接口，初始化时钟、reset，提供tcon-tv0、tcon-tv1、dsi时钟。

目前有r40、h6支持了tcon top。

### sun4i tcon

### sun4i crtc

## 部分流程

针对有tcon top的版本：

```
drm_crtc_helper_funcs

	->mode_set_nofb(sun4i_crtc_mode_set_nofb)
		->sun4i_tcon0_mode_set_cpu
		
		->sun4i_tcon0_mode_set_lvds
		
		->sun4i_tcon0_mode_set_rgb
		->sun4i_tcon_set_mux
			->tcon->quirks->set_mux
			
		->sun4i_tcon1_mode_set
		->sun4i_tcon_set_mux
			->tcon->quirks->set_mux
				->sun8i_tcon_top_set_hdmi_src
				->sun8i_tcon_top_de_config
```

研究以下这几个API：

of_graph_get_endpoint_by_regs

of_graph_get_remote_endpoint

of_graph_parse_endpoint



of_graph_get_port_by_id

sun4i_tcon_of_get_id_from_port

of_graph_get_remote_node

