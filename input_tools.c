/*******************************************************************
  Project main function template for MicroZed based MZ_APO board
  designed by Petr Porazil at PiKRON
 
  include your name there and license for distribution.
 
  Remove next text: This line should not appear in submitted
  work and project name should be change to match real application.
  If this text is there I want 10 points subtracted from final
  evaluation.
 
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

void getValues ( unsigned char *mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    redValue = ( r>>16 )&0xff;
    blueValue = r&0xff;
    greenValue = ( r>>8 )&0xff;
}

int getRedValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return redValue;
}

int getRedMovement ( unsigned char *mem_base ) {
    int value = getRedValue( mem_base );
    printf( "Red value: %d\n", value );

    if ( value > 40 && value <= 128 ) {
        printf( "Red goes right.\n" );
        return 1;
    } else if ( value > 128 && value < 215 ) {
        printf( "Red goes left.\n" );
        return -1;
    }
    
    printf( "Red goes straight.\n" );
    return 0;
}

int getBlueValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return blueValue;
}

int getBlueMovement ( unsigned char *mem_base ) {
    int value = getBlueValue( mem_base );
    printf( "Blue value: %d\n", value );

    if ( value > 40 && value <= 128 ) {
        printf( "Blue goes right.\n" );
        return 1;
    } else if ( value > 128 && value < 215 ) {
        printf( "Blue goes left.\n" );
        return -1;
    }
    
    printf( "Blue goes straight.\n" );
    return 0;
}

int getGreenValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return greenValue;
}

int getGreenMovement ( unsigned char *mem_base ) {
    int value = getGreenValue( mem_base );
    printf( "Green value: %d\n", value );

    if ( value > 40 && value <= 128 ) {
        printf( "Green goes right.\n" );
        return 1;
    } else if ( value > 128 && value < 215 ) {
        printf( "Green goes left.\n" );
        return -1;
    }
    
    printf( "Green goes straight.\n" );
    return 0;
}