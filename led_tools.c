/*******************************************************************
  led_tools.c containing functions for manipulating with the 
  LEDs.
 
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

void changeLengthLed ( unsigned short length1, unsigned short length2, unsigned char* mem_base ) {
    short ones1 = length1 % 10;
    short tens1 = ( length1 - ones1 ) / 10;
    short ones2 = length2 % 10;
    short tens2 = ( length2 - ones2 ) / 10;

    int finalValue = 0;
    
    for ( int i = 0; i < ones2; ++i ) {
        int power = 1;
        for ( int j = 0; j < i; ++j ) {
            power *= 2;
        }
        finalValue += power;
    }

    for ( int i = 15; i > 15 - tens2 && i > 8; --i ) {
        int power = 1;
        for ( int j = 0; j < i; ++j ) {
            power *= 2;
        }
        finalValue += power;
    }

    for ( int i = 31; i > 31 - ones1; --i ) {
        int power = 1;
        for ( int j = 0; j < i; ++j ) {
            power *= 2;
        }
        finalValue += power;
    }

    for ( int i = 16; i < 16 + tens1 && i < 23; ++i ) {
        int power = 1;
        for ( int j = 0; j < i; ++j ) {
            power *= 2;
        }
        finalValue += power;
    }

    *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_LINE_o ) = finalValue;
}