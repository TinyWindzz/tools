WQ_POWER_EFFICIENT这个配置只会影响system_power_efficient_wq和system_freezable_power_efficient_wq的行为，如果配置WQ_POWER_EFFICIENT，会将其修改为WQ_UNBOUND。

unbound worker_pool 相对应的意思，就是 worker 可以在多个 CPU 上调度的。但是他其实也是绑定的，只不过它绑定的单位不是 CPU 而是 node。所谓的 node 是对 NUMA(Non Uniform Memory Access Architecture) 系统来说的，NUMA 可能存在多个 node，每个 node 可能包含一个或者多个 CPU。???

bound型可能导致处于idle的CPU被唤醒，而unbound型则不会必然唤醒idle的CPU。???

__WQ_ORDERED是什么？？？

wq_select_unbound_cpu逻辑是啥？？？

```c
system_power_efficient_wq = alloc_workqueue("events_power_efficient",
                                            WQ_POWER_EFFICIENT, 0);

queue_delayed_work(system_power_efficient_wq, &driver->wq_extcon,
                   driver->debounce_jiffies);
```



```c
pool_workqueue		pwq				//中介
workqueue_struct	wq									//works
work_struct 		work 	/	delayed_work 	dwork	//work

worker_pool			//workers	
worker				//内核线程

//pool_workqueue用于链接workqueue_struct和worker_pool。
//workqueue_struct 和 pool_workqueue 是一对多的关系。
//pool_workqueue 和 worker_pool 是一对一的关系。
```

worker_pool是per-cpu变量，每个CPU都有worker_pool，而且有两个worker_pool。
create_worker()创建内核的工作线程。资源紧张时，有可能创建更多的worker。


```c
create_worker
	->set_user_nice
	->kthread_bind_mask		//设置了内核线程亲和性
```
