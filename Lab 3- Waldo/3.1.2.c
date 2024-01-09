/* Name: 3.1.2.c
 * Author: Kevin Paulose
 * Description: Sub-routines as per Lab question 3.1.2
 */

#include "MEAM_general.h"  // include resources from MEAM_general.h file
#include "m_usb.h"         // include resources from m_usb.h file

void setup_ADC(unsigned int pin) {
    // first time setup tasks
    static int firstTime;
    if (!firstTime) {
        set(ADMUX, REFS0);  // set reference voltage to 5V / Vcc

        // set ADC clock pre-scaler of /128 = 125kHz
        set(ADCSRA, ADPS0);
        set(ADCSRA, ADPS1);
        set(ADCSRA, ADPS2);
    }

    // disable ADC pin digital input
    if (pin > 8) {
        set(DIDR2, pin - 8); //pins 8-13 are to be set from 0-5
    } else {
        set(DIDR0, pin); //pins of this bunch are to be set respective to their pin numbers
    }

    // select ADC channel based on the joint
    // MUX5 bit assignment
    if (pin > 7) {
        set(ADCSRB, MUX5);
    } else {
        clear(ADCSRB, MUX5);
    }
    // MUX2 bit assignment
    if (pin == 4 || pin == 5 || pin == 6 || pin == 7 || pin == 12|| pin == 13) {
        set(ADMUX, MUX2);
    } else {
        clear(ADMUX, MUX2);
    }
    // MUX1 bit assignment
    if (pin == 6 || pin == 7 || pin == 10 || pin == 11 ) {
        set(ADMUX, MUX1);
    } else {
        clear(ADMUX, MUX1);
    }
    // MUX0 bit assignment
    if (pin % 2 == 1) {
        set(ADMUX, MUX0);
    } else {
        clear(ADMUX, MUX0);
    }

    set(ADCSRA, ADEN);    // enable ADC
    firstTime = 1;  // so that the loop runs every time like its first time
}

//Read ADC ports
unsigned int read_ADC() {
    set(ADCSRA, ADSC);                 // start conversion
    while(!bit_is_set(ADCSRA, ADIF));  // wait for conversion to finish
    set(ADCSRA, ADIF);                 // clear the conversion complete flag
    return ADC;
}

// int main(void) {
//     m_usb_init();     // initialize serial port
//     _clockdivide(0);  // set clock speed to 16 MHz

//     //serial putty output of joint information
//     for (;;) {
//     }
// }