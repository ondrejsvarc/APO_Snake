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

int getRedValue () {
    unsigned char *parlcd_mem_base, *mem_base;

    parlcd_mem_base = map_phys_address( PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0 );
    if ( parlcd_mem_base == NULL ) exit( 1 );
 
    mem_base = map_phys_address( SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0 );
    if ( mem_base == NULL ) exit( 1 );
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    return ( r>>16 )&0xff;
}

int getRedMovement () {
    int value = getRedValue();
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

int getBlueValue () {
    unsigned char *parlcd_mem_base, *mem_base;

    parlcd_mem_base = map_phys_address( PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0 );
    if ( parlcd_mem_base == NULL ) exit( 1 );
 
    mem_base = map_phys_address( SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0 );
    if ( mem_base == NULL ) exit( 1 );
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    return r&0xff;
}

int getBlueMovement () {
    int value = getBlueValue;
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

int getGreenValue () {
    unsigned char *parlcd_mem_base, *mem_base;

    parlcd_mem_base = map_phys_address( PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0 );
    if ( parlcd_mem_base == NULL ) exit( 1 );
 
    mem_base = map_phys_address( SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0 );
    if ( mem_base == NULL ) exit( 1 );
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    return ( r>>8 )&0xff;
}

int getGreenMovement () {
    int value = getGreenValue;
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