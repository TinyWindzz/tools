// SPDX-License-Identifier: GPL-2.0
/*
 *  Copyright(C) 2019, Frank <tiny.windzz@gmail.com>
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>

#define ALIGN 0x1000

void dump_mem(char *addr, unsigned int start, unsigned int length)
{
    unsigned int cur = start;
    int *p = (int *)addr;

    while (cur < start + length) {
        char i = 0;

        printf("0x%x:\t", cur);
        for (;i < 4 && cur < start + length; i++, cur += 4, p++)
            printf("0x%-10x    ", *p);
        printf("\n");
    }
}

/*
 *  TODO: add write function and increase friendliness
 */
int main(int argc, char **argv)
{
    unsigned char * map_base;
    unsigned int start, length;
    int fd;

    if (argc != 3) {
        printf("Usage: ./dev-mem [addr] [length]\n");
        printf("Notice: [addr] must be aligned in word size!\n");
        return 0;
    }

    start = strtol(argv[1], NULL, 0);
    length = strtol(argv[2], NULL, 0);

    fd = open("/dev/mem", O_RDWR|O_SYNC);
    if (fd < 0)
        return -1;

    map_base = mmap(NULL, length + start % ALIGN, PROT_READ|PROT_WRITE,
                    MAP_SHARED, fd, start / ALIGN * ALIGN);
    if (!map_base) {
        printf("map error\n");
        return -1;
    }

    /* printf mem */
    dump_mem(map_base + start % ALIGN, start, length);

    close(fd);
    munmap(map_base, 0xff);

    return 0;
}
