#include "rgb_tools.h"

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

void changeRedRGBLED ( int status, unsigned char* mem_base) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o );

    switch ( status ) {
    case 0:
        // Alive
        r = 0x7e0;
        break;
    case 1:
        // Fruit
        break;
    case 2:
        // Dead
        break;
    default:
        break;
    }
}

void changeBlueRGBLED ( int status, unsigned char* mem_base) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o );

    switch ( status ) {
    case 0:
        // Alive
        r = 0x7e0;
        break;
    case 1:
        // Fruit
        break;
    case 2:
        // Dead
        break;
    default:
        break;
    }
}