/* Name: main.c
 * Author: Kevin Paulose
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

int main(void)
{
    _clockdivide(0); //setting the clock speed at 16MHz
    set_led(ON); //Turn on the on-board LED
    _delay_ms(1000); //1000ms wait time

    set(DDRB, 6); //Set Port B6 as output

    for(;;){
        // set_led(TOGGLE); //Toggle (switch) on-board LED state
        toggle(PORTB,6); // Switch external LED state
        _delay_ms(1000); //LED blinks at every 1000ms = 1s
    }

    return 0;
}
