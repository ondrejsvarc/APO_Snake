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


unsigned short *fb;

int main(int argc, char *argv[]) {
  unsigned char *mem_base;
  unsigned char *parlcd_mem_base;
  uint32_t val_line=5;
  int i,j,k;
  unsigned int c;
  
  fb = (unsigned short*)malloc(320*480*2);
  printf("Hello world\n");

  sleep(1);

  /*
   * Setup memory mapping which provides access to the peripheral
   * registers region of RGB LEDs, knobs and line of yellow LEDs.
   */
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

  /* If mapping fails exit with error code */
  if (mem_base == NULL)
    exit(1);

  struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 20 * 1000 * 1000};
  for (i=0; i<30; i++) {
     *(volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o) = val_line;
     val_line<<=1;
     printf("LED val 0x%x\n", val_line);
     clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
  
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

  if (parlcd_mem_base == NULL)
    exit(1);

  parlcd_hx8357_init(parlcd_mem_base);

  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (i = 0; i < 320 ; i++) {
    for (j = 0; j < 480 ; j++) {
      c = 0;
      parlcd_write_data(parlcd_mem_base, c);
    }
  }
  parlcd_write_cmd(parlcd_mem_base, 0x2c);

  drawTile(50, 0x7ff, fb);
  drawFruit(100, fb);

for(int ptr = 0; ptr < 480*320; ptr++) {
  parlcd_write_data(parlcd_mem_base, fb[ptr]);
}

parlcd_write_cmd(parlcd_mem_base, 0x2c);


  


  printf("Goodbye world\n");

  return 0;
}