/* Name: main.c
 * Author: Kevin Paulose
 * Code for: 2.1.4
 */

#include "MEAM_general.h"

// Define constants for pinMode using preprocessor #define directives
#define INPUT 1 // Input without pullup pin
#define INPUT_PULLUP 2 // Input with pullup pin
#define OUTPUT 3 // Output port

// Macro to set the mode of a pin
#define pinMode(register, bit, mode)
    do { \
        if (mode == INPUT) 
        {
            clear(register, bit);  // Clear the bit in DDRx to configure as input
            set(register, bit);    // Set the bit in PORTx to enable the pull-up resistor
        }
        else if (mode == INPUT_PULLUP) 
        {
            clear(register, bit);  // Clear the bit in DDRx to configure as input
            set(register, bit);    // Set the bit in PORTx to enable the pull-up resistor
        }
        else if (mode == OUTPUT) 
        {
            set(register, bit);    // Set the bit in DDRx as output
        }
    } while (0)
