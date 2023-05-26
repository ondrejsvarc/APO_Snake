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

void reset_RGB_LED ( unsigned char* mem_base ) {
    *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = 0x0;
    *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = 0x0;
}

void changeRedRGBLED ( int status, unsigned char* mem_base) {

    switch ( status ) {
    case 0:
        // Alive
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = 0xff00;
        break;
    case 1:
        // Fruit
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = 0xff;
        break;
    case 2:
        // Dead
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = 0xff0000;
        break;
    default:
        break;
    }
}

void changeBlueRGBLED ( int status, unsigned char* mem_base) {

    switch ( status ) {
    case 0:
        // Alive
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = 0xff00;
        break;
    case 1:
        // Fruit
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = 0xff;
        break;
    case 2:
        // Dead
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = 0xff0000;
        break;
    default:
        break;
    }
}