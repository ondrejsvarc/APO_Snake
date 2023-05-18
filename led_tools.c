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

bool values[32];

void getValues ( int* r ) {
    for ( int i = 0; i < 32; ++i ) {
        values[i] = ( r>>i )&0x01;
    }
}

void pasteValues ( int* r ) {
    for ( int i = 0; i < 32; ++i ) {
        ( r>>i )&0x01 = values[i];
    }
}

void changeRedLengthLed ( unsigned short length, unsigned char* mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_LINE_o );
    getValues( r );

    short ones = length % 10;
    short tens = ( length - ones ) / 10;
    
    int iterator = 0;
    for ( short i = 31; i > 22; --i ) {
        if ( iterator < ones ) {
            values[i] = true;
        } else {
            values[i] = false;
        }
        iterator++;
    }

    iterator = 0;
    for ( short i = 16; i < 23; ++i ) {
        if ( iterator < tens ) {
            values[i] = true;
        } else {
            values[i] = false;
        }
        iterator++;
    }

    pasteValues( r );
}

void changeBlueLengthLed ( unsigned short length, unsigned char* mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_LINE_o );
    getValues( r );

    short ones = length % 10;
    short tens = ( length - ones ) / 10;
    
    int iterator = 0;
    for ( short i = 0; i < 9; ++i ) {
        if ( iterator < ones ) {
            values[i] = true;
        } else {
            values[i] = false;
        }
        iterator++;
    }

    iterator = 0;
    for ( short i = 15; i > 8; --i ) {
        if ( iterator < tens ) {
            values[i] = true;
        } else {
            values[i] = false;
        }
        iterator++;
    }

    pasteValues( r );
}