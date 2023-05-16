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

int getDirection ( int value ) {
    if ( value > 16 && value <= 40 ) {
        printf( "Goes right.\n" );
        return 1;
    } else if ( value > 40 && value < 64 ) {
        printf( "Goes left.\n" );
        return -1;
    }
    
    printf( "Goes straight.\n" );
    return 0;
}

int getRedValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return redValue;
}

int getRedMovement ( unsigned char *mem_base, int initialValue ) {
    int value = ( getRedValue( mem_base ) - initialValue ) % 80;
    value = value < 0 ? ( value + 240 ) % 80 : value;
    printf( "Red value: %d\n", value );
    return getDirection( value );
}

int getBlueValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return blueValue;
}

int getBlueMovement ( unsigned char *mem_base, int initialValue ) {
    int value = ( getBlueValue( mem_base ) - initialValue ) % 80;
    value = value < 0 ? ( value + 240 ) % 80 : value;
    printf( "Blue value: %d\n", value );

    return getDirection( value );
}

int getGreenValue ( unsigned char *mem_base ) {
    getValues( mem_base );
    return greenValue;
}

int getGreenMovement ( unsigned char *mem_base, int initialValue ) {
    int value = ( getGreenValue( mem_base ) - initialValue ) % 80;
    value = value < 0 ? ( value + 240 ) % 80 : value;
    printf( "Green value: %d\n", value );

    return getDirection( value );
}