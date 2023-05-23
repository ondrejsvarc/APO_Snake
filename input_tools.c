/*******************************************************************
  input_tools.c containing functions for translating knob movements to
  change of directions.
 
  Created by Ondrej Svarc and Michal Komanec.
 
 *******************************************************************/
 
#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

unsigned char redValue = 0;
unsigned char blueValue = 0;
unsigned char greenValue = 0;

bool pressGreen ( unsigned char *mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    if ( ( r&0x7000000 ) != 0 ) {
        return true;
    }
    return false;
}

void getValues ( unsigned char *mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    redValue = ( r>>16 )&0xff;
    blueValue = r&0xff;
    greenValue = ( r>>8 )&0xff;
}

int getDirection ( int value, int previousValue ) {
    int compValue = value + 256;
    int compPreviousValue = previousValue + 256;
    if ( compValue > compPreviousValue ) {
        //printf( "Goes right.\n" );
        return 1;
    } else if ( compValue < compPreviousValue ) {
        //printf( "Goes left.\n" );
        return -1;
    }
    //printf( "Goes straight.\n" );
    return 0;
}

int getRedValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return redValue;
}

int getRedMovement ( unsigned char *mem_base, int previousValue ) {
    int value = getRedValue( mem_base );
    //printf( "Red value: %d\n", value );
    return getDirection( value, previousValue );
}

int getBlueValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return blueValue;
}

int getBlueMovement ( unsigned char *mem_base, int previousValue ) {
    int value = getBlueValue( mem_base );
    //printf( "Blue value: %d\n", value );
    return getDirection( value, previousValue );
}

int getGreenValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return greenValue;
}

int getGreenMovement ( unsigned char *mem_base, int previousValue ) {
    int value = getGreenValue( mem_base );
    //printf( "Green value: %d\n", value );
    return getDirection( value, previousValue );
}