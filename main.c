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
#include "input_tools.h"


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

    

    fb = (unsigned short *)malloc(320*480*sizeof(unsigned short));
    if (fb == NULL) {
        fprintf(stderr, "Couldn't allocate memory for frame buffer!");
        exit(1);
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

    drawMenu(fb);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    short menu_choice = 0;
    int old_green_val = getGreenValue(mem_base);
    short move;

    while (1) {
        move = getGreenMovement(mem_base, old_green_val);
        old_green_val = getGreenValue(mem_base);

        if (move != 0) {
            drawMenuChoice(menu_choice, 0, fb);

            if (move == -1) {
                menu_choice = menu_choice == 0 ? 3 : menu_choice-1;
            } else if (move == 1) {
                menu_choice = (menu_choice+1)%4;
            }

            drawMenuChoice(menu_choice, COLOR_GREEN, fb);

            for (int i = 0; i < 320*480; i++) {
                parlcd_write_data(parlcd_mem_base, fb[i]);
            }
            parlcd_write_cmd(parlcd_mem_base, 0x2c);

        }
    }



    return 0;
}