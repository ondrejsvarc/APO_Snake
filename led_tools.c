#include "led_tools.h"
 
void change_LED_strip_length (unsigned short length1, unsigned short length2, unsigned char* mem_base ) {
    // Get ones and tens of the lengths
    short ones1 = length1 % 10;
    short tens1 = ( length1 - ones1 ) / 10;
    short ones2 = length2 % 10;
    short tens2 = ( length2 - ones2 ) / 10;

    // Create final value
    int finalValue = 0;
    
    // Add powers of 2 to the final value based on leds that should be turned on
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

    // Turn on the leds
    *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_LINE_o ) = finalValue;
}