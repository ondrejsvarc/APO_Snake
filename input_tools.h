/*******************************************************************
  input_tools.h containing functions for translating knob movements to
  change of directions and different user inputs.
 
  Created by Ondrej Svarc and Michal Komanec.
 
 *******************************************************************/

#define _POSIX_C_SOURCE 200112L
 
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>            //termios, TCSANOW, ECHO, ICANON
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

/**
 * Checks if both the red and blue knobs are pressed simultaneously.
 *
 * @param mem_base The memory base address.
 * @return True if both knobs are pressed, false otherwise.
 */
bool abort_game ( unsigned char *mem_base );

/**
 * Checks if the green knob is pressed.
 *
 * @param mem_base The memory base address.
 * @return True if the green knob is pressed, false otherwise.
 */
bool pressGreen ( unsigned char *mem_base );

/**
 * Retrieves the values of the red, green, and blue knobs.
 *
 * @param mem_base The memory base address.
 */
void get_values ( unsigned char *mem_base );

/**
 * Determines the change in direction based on the values of the current and previous positions.
 *
 * @param value         The current position value.
 * @param previousValue The previous position value.
 * @return              The change in direction as a movement (-1 for left, 1 for right, 0 for straight).
 */
int get_direction ( int value, int previousValue );

/**
 * Retrieves the value of the red knob.
 *
 * @param mem_base  Base address of the memory mapping.
 * @return          The value of the red knob.
 */
int getRedValue ( unsigned char *mem_base );

/**
 * Retrieves the movement direction of the red knob.
 *
 * @param mem_base       Base address of the memory mapping.
 * @param previousValue  The previous value of the red knob.
 * @return               The movement direction of the red knob (-1 for left, 1 for right, 0 for straight).
 */
int getRedMovement ( unsigned char *mem_base, int previousValue );

/**
 * Retrieves the value of the blue knob.
 *
 * @param mem_base  Base address of the memory mapping.
 * @return          The value of the blue knob.
 */
int getBlueValue ( unsigned char *mem_base );

/**
 * Retrieves the movement direction of the blue knob.
 *
 * @param mem_base       Base address of the memory mapping.
 * @param previousValue  The previous value of the blue knob.
 * @return               The movement direction of the blue knob (-1 for left, 1 for right, 0 for straight).
 */
int getBlueMovement ( unsigned char *mem_base, int previousValue );

/**
 * Retrieves the value of the green knob.
 *
 * @param mem_base  Base address of the memory mapping.
 * @return          The value of the green knob.
 */
int getGreenValue ( unsigned char *mem_base );

/**
 * Retrieves the movement direction of the green knob.
 *
 * @param mem_base       Base address of the memory mapping.
 * @param previousValue  The previous value of the green knob.
 * @return               The movement direction of the green knob (-1 for left, 1 for right, 0 for straight).
 */
int getGreenMovement ( unsigned char *mem_base, int previousValue );