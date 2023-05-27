#include "input_tools.h"

unsigned char redValue = 0;
unsigned char blueValue = 0;
unsigned char greenValue = 0;

bool abort_game ( unsigned char *mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    // Check if red and blue knobs are pressed
    if ( ( r&0x1000000 ) != 0 && ( r&0x4000000 ) != 0 ) {
        return true;
    }
    return false;
}

bool green_pressed (unsigned char *mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    // Check if green knob is pressed
    if ( ( r&0x2000000 ) != 0 ) {
        return true;
    }
    return false;
}

void get_values ( unsigned char *mem_base ) {
    int r = *( volatile uint32_t * ) ( mem_base + SPILED_REG_KNOBS_8BIT_o );

    // Get values of all knobs
    redValue = ( r>>16 )&0xff;
    blueValue = r&0xff;
    greenValue = ( r>>8 )&0xff;
}

int get_direction ( int value, int previousValue ) {
    int compValue = value + 256;
    int compPreviousValue = previousValue + 256;
    // Compare values and return change of direction as a movement
    if ( compValue > compPreviousValue + 3) {
        // Right
        return 1;
    } else if ( compValue < compPreviousValue - 3) {
        // Left
        return -1;
    }
    // Straight
    return 0;
}

int get_red_value (unsigned char *mem_base ) {
    get_values( mem_base );
    return redValue;
}

int get_red_movement (unsigned char *mem_base, int previousValue ) {
    int value = get_red_value(mem_base);
    return get_direction( value, previousValue );
}

int get_blue_value (unsigned char *mem_base ) {
    get_values( mem_base );
    return blueValue;
}

int get_blue_movement (unsigned char *mem_base, int previousValue ) {
    int value = get_blue_value(mem_base);
    return get_direction( value, previousValue );
}

int get_green_value (unsigned char *mem_base ) {
    get_values( mem_base );
    return greenValue;
}

int get_green_movement (unsigned char *mem_base, int previousValue ) {
    int value = get_green_value(mem_base);
    return get_direction( value, previousValue );
}