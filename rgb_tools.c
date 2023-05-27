#include "rgb_tools.h"

void reset_RGB_LED ( unsigned char* mem_base ) {
    // Turn of the RGB LEDs
    *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = LED_OFF;
    *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = LED_OFF;
}

void changeRedRGBLED ( int status, unsigned char* mem_base) {

    switch ( status ) {
    case 0:
        // Alive
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = LED_GREEN;
        break;
    case 1:
        // Fruit
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = LED_BLUE;
        break;
    case 2:
        // Dead
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB1_o ) = LED_RED;
        break;
    default:
        break;
    }
}

void changeBlueRGBLED ( int status, unsigned char* mem_base) {

    switch ( status ) {
    case 0:
        // Alive
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = LED_GREEN;
        break;
    case 1:
        // Fruit
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = LED_BLUE;
        break;
    case 2:
        // Dead
        *( volatile uint32_t * ) ( mem_base + SPILED_REG_LED_RGB2_o ) = LED_RED;
        break;
    default:
        break;
    }
}