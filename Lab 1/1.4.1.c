/* Name: main.c
 * Author: Kevin Paulose
 */

#include "MEAM_general.h"  

int main(void)
{
    set(DDRC, 6); //Set PORTC 6 as output 
    set(TCCR3B, WGM32); //Set timer mode 3
    set(TCCR3A, WGM30);
    set(TCCR3B, CS30); // pre-scaler /1
    set(TCCR3A, COM3A1);  //set output compare mode to clear OC3A on compare match
    // set(PORTC, 6);

    int delay_time = 50; //Time needed for each increment/decrement in ms
    float duty_cycle = 60; 

    //brightness step counter
    float bright_inc = delay_time/0.3; //Number of increments to reach full intensity
    float bright_dec = delay_time/0.6; //Number of decrements to reach zero intensity



    for (;;){
        for(duty_cycle = 0; duty_cycle <= 100; duty_cycle += bright_inc){
        OCR3A = (255*duty_cycle) / 100; 
        //Scales duty_cycle from percentage to value suitable for an 8-bit PWM timer
        _delay_ms(delay_time); //Wait time between each cycle change
        }
        
        for(duty_cycle = 100; duty_cycle >= 0; duty_cycle -= bright_dec){
        OCR3A = (255*duty_cycle) / 100;
        _delay_ms(delay_time);
        }

    }
    return 0;
}
