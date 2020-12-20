[TOC]

## trace-cmd 工具

### stack trace

```c
//对dev_pm_opp_of_remove_table的调用栈做一个trace
 
~ # trace-cmd reset
~ # trace-cmd record -p function -l dev_pm_opp_of_remove_table --func-stack &
~ # kill -2 211
~ # trace-cmd report

  unknown option 9
CPU 1 is empty
CPU 2 is empty
CPU 3 is empty
cpus=4
           rmmod-217   [000]  2141.684133: function:             dev_pm_opp_of_remove_table <-- 0x7f000024
           rmmod-217   [000]  2141.684255: kernel_stack:         	=> 0x7f000024s
	=> platform_drv_remove
	=> device_release_driver_internal
	=> driver_detach
	=> bus_remove_driver
	=> driver_unregister
	=> platform_driver_unregister
	=> 0x7f000168s
```

### function trace

```c
//trace函数是否执行

~ # trace-cmd reset
~ # trace-cmd  record -p function -l dev_pm_opp_of_remove_table -l dev_pm_opp_put_regulators -l dev_pm_opp_put_supported_hw  &
~ # kill -2 211
~ # trace-cmd report
    
  unknown option 9
CPU 1 is empty
CPU 2 is empty
CPU 3 is empty
cpus=4
           rmmod-264   [000]  3035.731115: function:             dev_pm_opp_of_remove_table <-- 0x7f000024
           rmmod-264   [000]  3035.731683: function:             dev_pm_opp_put_regulators <-- 0x7f00002c
           rmmod-264   [000]  3035.731955: function:             dev_pm_opp_put_supported_hw <-- 0x7f000034
```

