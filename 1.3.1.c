/* Name: main.c
 * Author: Kevin Paulose
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define COMPAREVALUE 6250 // = (25ms)*250 KHZ -> VALUE FOR 64 PRESCALER (16MHZ/64 = 250kHz)

int main(void)
{
    set(DDRB, 6); //Sets the Data Direction Register (DDRB) bit at position 6 to 1
    set(TCCR3B, CS30); //Timer 3 control register ->1
    set(TCCR3B, CS31); //Timer 3 control register ->1
    //clear(TCCR3B, CS32); //Timer 3 control register ->0
    
    set(PORTB, 6); //Set PORTB 6 as output
    for (;;){
        if (TCNT3 > COMPAREVALUE){ 
            toggle(PORTB, 6); 
            TCNT3 = 0; //Reset the timer to 0
        }
    }
    return 0;
}
