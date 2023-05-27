/*******************************************************************
  led_tools.c containing functions for manipulating the 
  LED stripe.
 
  Created by Ondrej Svarc and Michal Komanec.
 
 *******************************************************************/

#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

/**
 * Changes the LED stripe based on the given lengths.
 *
 * @param length1 An unsigned short representing the first length value.
 * @param length2 An unsigned short representing the second length value.
 * @param mem_base A pointer to the base address of the memory mapping.
 */
void change_LED_strip_length (unsigned short length1, unsigned short length2, unsigned char* mem_base );
