/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

int main(void)
{
    int dutyCycle = 60;
    float offtime = (float)dutyCycle/100;
    float ontime = 1.0-offtime;

    set(DDRB, 6);
    set (PORTB, 6);

    /* insert your hardware initialization here */
    for(;;){
        /* insert your main loop code here */
        toggle(PORTB,6);		// wait
        _delay_ms(1000.0*offtime);
        toggle(PORTB,6);		// wait
        _delay_ms(1000.0*ontime); 
    }
    return 0;   /* never reached */
}
