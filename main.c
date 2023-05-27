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
#include "led_tools.h"
#include "input_tools.h"
#include "font_types.h"
#include "rgb_tools.h"
#include "game.h"

// global variables/pointers declaration
unsigned short *fb;
unsigned char *mem_base;
unsigned char *parlcd_mem_base;

void start_menu();

int main(int argc, char *argv[]) {
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL) {
      exit(1);
  }

  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL) {
      exit(1);
  }
  parlcd_hx8357_init(parlcd_mem_base);

  // allocate memory for frame buffer
  fb = (unsigned short *)malloc(320*480*sizeof(unsigned short));
  if (fb == NULL) {
      fprintf(stderr, "Couldn't allocate memory for frame buffer!");
      exit(1);
  }

  // open menu
  start_menu();

  printf("\nSefe, mne se asi neco nepovedlo.\n\n");
  return 0;
}

/*Open game menu, show options and interact with user.*/
void start_menu() {
  // reset LEDs
    change_LED_strip_length(0, 0, mem_base);
  reset_RGB_LED(mem_base);

  // draw menu image
    draw_menu(fb);

  // write frame buffer to LCD display
  for (int i = 0; i < 320*480; i++) {
      parlcd_write_data(parlcd_mem_base, fb[i]);
  }
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  // initialize menu variables
  short menu_choice = 0;
  short diff_choice = 0;

  long int speed_choices[3] = {SPEED_EASY, SPEED_MEDIUM, SPEED_HARD};

  int old_green_val = get_green_value(mem_base);
  int old_blue_val = get_blue_value(mem_base);

  short move_green;
  short move_blue;

  while (1) {
      // handle encoders
      move_green = get_green_movement(mem_base, old_green_val);
      move_blue = get_blue_movement(mem_base, old_blue_val);
      if (move_green != 0) {
        old_green_val = get_green_value(mem_base);
      }
      if (move_blue != 0) {
        old_blue_val = get_blue_value(mem_base);
      }
      // check if green encoder has been pressed - start games or exit
      if (green_pressed(mem_base)) {
        switch (menu_choice) {
          case 0: 
            start_zero_players_game(speed_choices[diff_choice], fb, mem_base, parlcd_mem_base);
            break;
          case 1:
            start_one_player_game(speed_choices[diff_choice], fb, mem_base, parlcd_mem_base);
            break;
          case 2:
            start_two_players_game(speed_choices[diff_choice], fb, mem_base, parlcd_mem_base);
            break;
          case 3:
            // blackout frame buffer and LCD display
            paint_it_black(fb);
            for (int i = 0; i < 320*480; i++) {
              parlcd_write_data(parlcd_mem_base, fb[i]);
            }
            parlcd_write_cmd(parlcd_mem_base, 0x2c);
            // reset LEDs and exit
                change_LED_strip_length(0, 0, mem_base);
            reset_RGB_LED(mem_base);
            return;
        }
        // the game ended and the program is back in the menu state, reset LEDs and menu variables and draw menu
          change_LED_strip_length(0, 0, mem_base);
        reset_RGB_LED(mem_base);
          draw_menu(fb);

        menu_choice = 0;
        diff_choice = 0;

        old_green_val = get_green_value(mem_base);
        old_blue_val = get_blue_value(mem_base);

          draw_menu_choice(menu_choice, COLOR_GREEN, fb);
          draw_difficulty_choice(diff_choice, fb);

        for (int i = 0; i < 320*480; i++) {
          parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);

        // sleep for 1 sec to not start a new game accidentally
        struct timespec loop_delay = {.tv_sec = 1, .tv_nsec = 0};
        clock_nanosleep(1, 0, &loop_delay, NULL);

      }

      // check if menu choice has changed
      if (move_green != 0) {
        // black out the old choice
          draw_menu_choice(menu_choice, COLOR_BLACK, fb);
        // handle menu choice variable
        if (move_green == -1) {
          menu_choice = menu_choice == 0 ? 3 : menu_choice-1;
        } else if (move_green == 1) {
          menu_choice = (menu_choice+1)%4;
        }
        // draw new menu choice
          draw_menu_choice(menu_choice, COLOR_GREEN, fb);

        // write frame buffer to LCD display
        for (int i = 0; i < 320*480; i++) {
            parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);
      }
      
      // check if difficulty choice has changed
      if (move_blue != 0) {
        // handle menu choice variable
        if (move_blue == -1) {
            diff_choice = diff_choice == 0 ? 2 : diff_choice-1;
        } else if (move_blue == 1) {
            diff_choice = (diff_choice+1)%3;
        }
        // draw new difficulty choice
          draw_difficulty_choice(diff_choice, fb);

        // write frame buffer to LCD display
        for (int i = 0; i < 320*480; i++) {
            parlcd_write_data(parlcd_mem_base, fb[i]);
        }
        parlcd_write_cmd(parlcd_mem_base, 0x2c);
      }

  }
  return;
}