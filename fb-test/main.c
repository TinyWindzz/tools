// SPDX-License-Identifier: GPL-2.0
/*
 *  Copyright(C) 2019, Frank <tiny.windzz@gmail.com>
 */
#include <unistd.h>  
#include <stdio.h>  
#include <fcntl.h>  
#include <linux/fb.h>  
#include <sys/mman.h>  
#include <stdlib.h>  
#include <string.h>
#include <sys/ioctl.h>
#include <error.h>

#define FBDEV	"/dev/fb0"

#define handle_error(msg) \
		do { perror(msg); exit(EXIT_FAILURE); } while (0)

/*
 * For r/g/b color table:
 * https://www.114la.com/other/rgb.htm
 *
 * 31        16     8     0
 * +----------------------+
 * |	 | red |green|blue|
 * +----------------------+
 *
 */
void fill_color24(int *fb_addr, int bit_map, int psize)
{
	int i = 0;

	for(; i < psize; i++, fb_addr++)
		*fb_addr = bit_map;
}

void show_info(struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo)
{
	long screensize=0;  

	screensize = vinfo->xres * vinfo->yres * vinfo->bits_per_pixel / 8;  

	printf("The phy mem = 0x%lx, total size = %d(byte)\n",
	       finfo->smem_start, finfo->smem_len);  
	printf("xres =  %d, yres =  %d, bits_per_pixel = %d\n",
	       vinfo->xres, vinfo->yres, vinfo->bits_per_pixel);  
	printf("So the screensize = %ld(byte), using %ld frame\n",
	       screensize, finfo->smem_len/screensize);
	printf("vinfo.xoffset = %d, vinfo.yoffset = %d\n",
	       vinfo->xoffset, vinfo->yoffset);  
	printf("vinfo.vmode is :%d\n", vinfo->vmode);  
	printf("finfo.ypanstep is :%d\n", finfo->ypanstep);  
	printf("vinfo.red.offset=0x%x\n", vinfo->red.offset);
	printf("vinfo.red.length=0x%x\n", vinfo->red.length);
	printf("vinfo.green.offset=0x%x\n", vinfo->green.offset);
	printf("vinfo.green.length=0x%x\n", vinfo->green.length);
	printf("vinfo.blue.offset=0x%x\n", vinfo->blue.offset);
	printf("vinfo.blue.length=0x%x\n", vinfo->blue.length);
	printf("vinfo.transp.offset=0x%x\n", vinfo->transp.offset);
	printf("vinfo.transp.length=0x%x\n", vinfo->transp.length);
}

void fill_fb_info(int fd, struct fb_var_screeninfo *vinfo, struct fb_fix_screeninfo *finfo)
{
	if (ioctl(fd, FBIOGET_FSCREENINFO, finfo))
		exit(EXIT_FAILURE);

	if (ioctl(fd, FBIOGET_VSCREENINFO, vinfo))
		exit(EXIT_FAILURE);
}

int main(int argc, char **argv)   
{  
	int fd = 0;  
	struct fb_var_screeninfo *vinfo;  
	struct fb_fix_screeninfo *finfo;  
	char *fbp = NULL;    
	long location = 0;
	int value;
	long screensize = 0;  
	int pix_size = 0;

	if (argc != 2) {
		printf("Usage: ./fb-test [value]\n");
		return 0;
	}

	value = strtol(argv[1], NULL, 0);

	fd = open(FBDEV, O_RDWR);  
	if(fd < 0)
		handle_error("Can not open framebuffer device/n");

	vinfo = malloc(sizeof(*vinfo));
	if (!vinfo)
		handle_error("no mem");

	finfo = malloc(sizeof(*finfo));
	if (!finfo)
		handle_error("no mem");

	fill_fb_info(fd, vinfo, finfo);

	show_info(vinfo, finfo);

	screensize = vinfo->xres * vinfo->yres * vinfo->bits_per_pixel / 8;

	fbp =(char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fbp == MAP_FAILED)
		handle_error("failed to map framebuffer device to memory./n");
	printf("Get virt mem = %p\n", fbp);  

	pix_size = vinfo->xres * vinfo->yres;

	/* show color loop */
	printf("\ntip: green-0xE0EEE0\n");
	printf("\ndrawing ......\n");
	fill_color24((int *)fbp, value, pix_size);
        
	munmap(fbp, screensize);

	free(vinfo);
	free(finfo);
	close (fd);
	return 0;
}
