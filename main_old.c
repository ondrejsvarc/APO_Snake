#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "draw_tools.h"
#include "snake.h"
#include "led_tools.h"


unsigned short *fb;

int main(int argc, char *argv[]) {
    unsigned char *mem_base;
    unsigned char *parlcd_mem_base;
    mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (mem_base == NULL) {
        exit(1);
    }

    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcd_mem_base == NULL) {
       exit(1);
    }
    parlcd_hx8357_init(parlcd_mem_base);

    FILE *menu_img_file = fopen("/tmp/komanmi1/snake.ppm", "rb");
    if (menu_img_file == NULL) {
        fprintf(stderr, "Error opening snake.ppm");
        exit(1);
    }

    unsigned char *menu_img_buffer = (unsigned char*) malloc(320*480*3);
    if (menu_img_buffer == NULL) {
        fprintf(stderr, "Couldn't allocate memory for menu image buffer!");
        exit(1);
    }

    fb = (unsigned short *)malloc(320*480*sizeof(unsigned short));
    if (fb == NULL) {
        fprintf(stderr, "Couldn't allocate memory for frame buffer!");
        exit(1);
    }
    char *random_string = (char*)malloc(50);
    for (int i = 0; i < 4; i++) {
        fscanf(menu_img_file, "%s\n", random_string);
    }
    
    fread(menu_img_buffer, sizeof(unsigned char), 320*480*3, menu_img_file);
    for (int i = 0; i < 320*480; i++) {
        //fb[i] = (((((menu_img_buffer[i*3]/0xff)*0x3f)<<11)&0xf800) + ((((menu_img_buffer[i*3+1]/0xff)*0x7f)<<5)&0x7ff) + (((menu_img_buffer[i*3+2]/0xff)*0x3f)&0x1f));        
        fb[i] = (((((menu_img_buffer[i*3]/0xff)*0x3f)>>1)<<12) + ((((menu_img_buffer[i*3+1]/0xff)*0x7f)>>1)<<6)) + (((menu_img_buffer[i*3+2]/0xff)*0x3f)>>1);        
    }

    int c;
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int i = 0; i < 320 ; i++) {
        for (int j = 0; j < 480 ; j++) {
            c = 0;
            parlcd_write_data(parlcd_mem_base, c);
        }
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }

    parlcd_write_cmd(parlcd_mem_base, 0x2c);


    return 0;
}