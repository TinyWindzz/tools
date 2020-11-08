[TOC]

## Bitmap API

### 与、或、非、异或、与非操作

```c
bitmap_and			//与
bitmap_or			//或
bitmap_complement	//非
bitmap_xor			//异或
bitmap_andnot		//与非
```

### 置位、清零、填充

```c
bitmap_set		//置位操作
bitmap_clear	//清零操作
bitmap_zero		//清零操作
bitmap_fill 	//填充操作
```

## 遍历

```c
for_each_clear_bit_from		//从指定位置遍历 bitmap 清零 bit
for_each_clear_bit			//从头开始遍历 bitmap 清零 bit
for_each_set_bit			//从头开始遍历 bitmap 置位 bit
for_each_set_bit_from		//从指定位置开始遍历 bitmap 置位 bit
```



## Bitops API

## Bitmask



## 参考

https://biscuitos.github.io/blog/BITMAP