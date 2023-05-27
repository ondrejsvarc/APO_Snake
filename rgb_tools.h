/*******************************************************************
  rgb_tools.c containing functions for manipulating with the 
  RGB LEDs.
 
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


#define LED_RED 0xff0000
#define LED_BLUE 0xff
#define LED_GREEN 0xff00
#define LED_OFF 0x00
#define ALIVE_STATUS 0
#define FRUIT_STATUS 1
#define DEAD_STATUS 2

/**
 * Turns off the RGB LEDs.
 *
 * @param mem_base A pointer to the base address of the memory mapping.
 */
void reset_RGB_LED ( unsigned char* mem_base );

/**
 * Changes the status of the left RGB LED based on the provided status value.
 *
 * @param status The status value indicating the desired LED state:
 *               - 0: Alive (LED color: Green)
 *               - 1: Fruit (LED color: Blue)
 *               - 2: Dead (LED color: Red)
 * @param mem_base A pointer to the base address of the memory mapping.
 */
void changeRedRGBLED ( int status, unsigned char* mem_base);

/**
 * Changes the status of the right RGB LED based on the provided status value.
 *
 * @param status The status value indicating the desired LED state:
 *               - 0: Alive (LED color: Green)
 *               - 1: Fruit (LED color: Blue)
 *               - 2: Dead (LED color: Red)
 * @param mem_base A pointer to the base address of the memory mapping.
 */
void changeBlueRGBLED ( int status, unsigned char* mem_base);