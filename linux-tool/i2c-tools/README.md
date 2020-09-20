- 下载

  https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/

- 解压源码

- 指定交叉编译器

  export CC=aarch64-linux-gnu-gcc

  export STRIP=aarch64-linux-gnu-strip

  export AR=aarch64-linux-gnu-ar

- 编译

  make -j4

- 扩展

  如何使用静态库？

  加入USE_STATIC_LIB=1参数,如下:

  make -j4 USE_STATIC_LIB=1