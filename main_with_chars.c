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
#include "font_types.h"


unsigned short *fb;

/*
font_descriptor_t *fdes;
int scale=1;
 
void draw_pixel1(int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    fb[x+480*y] = color;
  }
}
 
void draw_pixel_big(int x, int y, unsigned short color) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel1(x+i, y+j, color);
    }
  }
}
 
int char_width(int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}
 
void draw_char(int x, int y, char ch, unsigned short color) {
  int w = char_width(ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(x+scale*j, y+scale*i, color);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

*/


int main(int argc, char *argv[]) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 100000000};
    //fdes = &font_winFreeSystem14x16;
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
    /*
    draw_char(350, 0, 'S', 0xffff);
    draw_char(361, 0, 'C', 0xffff);
    draw_char(372, 0, 'O', 0xffff);
    draw_char(383, 0, 'R', 0xffff);
    draw_char(394, 0, 'E', 0xffff);
    draw_char(403, 0, ':', 0xffff);
    */

    draw_score(420, 69, fb);
    //draw_char(0, 0, 'c', 0xffff, fb);

    for (int i = 0; i < 320*480; i++) {
        parlcd_write_data(parlcd_mem_base, fb[i]);
    }
    parlcd_write_cmd(parlcd_mem_base, 0x2c);

    short menu_choice = 0;
    short diff_choice = 0;
    int old_green_val = getGreenValue(mem_base);
    int old_blue_val = getBlueValue(mem_base);
    short move_green;
    short move_blue;

    while (1) {
        move_green = getGreenMovement(mem_base, old_green_val);
        move_blue = getBlueMovement(mem_base, old_blue_val);
        if (move_green != 0) {
          old_green_val = getGreenValue(mem_base);
        }
        if (move_blue != 0) {
          old_blue_val = getBlueValue(mem_base);
        }
        if (pressGreen(mem_base)) {
          switch (menu_choice) {
            case 0: 
              // sth
              // break;
              return 0;
            case 1:
              //sth
              break;
            case 2:
              //sth
              break;
            case 3:
              return 0;
          }
        }

        if (move_green != 0) {
            drawMenuChoice(menu_choice, 0, fb);
            
            if (move_green == -1) {
                menu_choice = menu_choice == 0 ? 3 : menu_choice-1;
            } else if (move_green == 1) {
                menu_choice = (menu_choice+1)%4;
            }

            drawMenuChoice(menu_choice, COLOR_GREEN, fb);

            for (int i = 0; i < 320*480; i++) {
                parlcd_write_data(parlcd_mem_base, fb[i]);
            }
            parlcd_write_cmd(parlcd_mem_base, 0x2c);

        }

        if (move_blue != 0) {
            if (move_blue == -1) {
                diff_choice = diff_choice == 0 ? 2 : diff_choice-1;
            } else if (move_blue == 1) {
                diff_choice = (diff_choice+1)%3;
            }

            drawDifficultyChoice(diff_choice, COLOR_GREEN, fb);

            for (int i = 0; i < 320*480; i++) {
                parlcd_write_data(parlcd_mem_base, fb[i]);
            }
            parlcd_write_cmd(parlcd_mem_base, 0x2c);

        }
       //clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL); 
    }

    printf("Bye!\n");
    return 0;
}