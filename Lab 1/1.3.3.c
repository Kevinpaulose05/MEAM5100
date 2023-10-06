/* Name: main.c
 * Author: Kevin Paulose
 */

#include "MEAM_general.h"  // includes the resources included in the MEAM_general.h file

#define duty_cycle 30 //Set duty cycle to 30%

int main(void)
{
    //Phase Correct PWM waveform
    set(DDRC, 6); //Set PORTC 6 as output 
    set(PORTC,6); 

    //Configure timer 3
    TCCR3B = (1<<WGM32)|(1<<CS30); //Set PWM with no prescaler (CS30).
    TCCR3A = (1<<WGM31)|(1<<WGM30)|(1<<COM3A1); //Set PWM (WGM30, WGM31) and Clear OC3A (COM3A1) on compare match.
    OCR3A = 1024*duty_cycle/100; //maximum value of 1024 (typical for 10-bit PWM)
    //Calculates OCR3A value to set the PWM duty cycle and Set to OCR3A

    set(TCCR3A,COM3A1); //Set COM3A1 on compare match when timer counts down
    clear(TCCR3A,COM3A0); //Clear COM3A0 on compare match when timer counts up
    return 0;
}
