/* Name: main.c
 * Author: Kevin Paulose
 * Code for: 2.3.2 and 2.4.2
 */

#include "MEAM_general.h"
#include "m_usb.h"

#define F_CPU 15625UL // 16Mz/1024 = 15625 Hz (/1024 prescaler)

int X, Y, Z, freq;

int main(void)
{
    _clockdivide(0); // Set the clock speed to 16MHz
    clear(DDRC, 7);    // PC7 output

    set(DDRB, 7); //Green LED (662 Hz)
    set(DDRB, 6); //Red LED (25 Hz)
    set(DDRB, 5); // Blue LED (200 Hz)

    m_usb_init();   

    for (;;)
    { 
        TCCR3B = 0x45; // {0100 0101}: configures TCNT3 for normal mode with /1024 prescaler and rising edge trigger for input capture
        while (!bit_is_set(TIFR3,ICF3));
        X = ICR3;
        set(TIFR3,ICF3);  //clears the Input Capture Flag (ICF3) by setting it to 1 for the next input capture event

        TCCR3B = 0x05; // {0000 0101}: CS30 and CS32 set to 1, rest bits cleared
        while (!bit_is_set(TIFR3,ICF3));
        Y = ICR3;
        set(TIFR3,ICF3); //clears the Input Capture Flag (ICF3) by setting it to 1 for the next input capture event
        
        TCCR3B = 0x45; // {0100 0101}: configures TCNT3 for normal mode with /1024 prescaler and rising edge trigger for input capture
        while (!bit_is_set(TIFR3,ICF3));
        Z = ICR3;
        set(TIFR3,ICF3); //clears the Input Capture Flag (ICF3) by setting it to 1 for the next input capture event
        
        if(X<Y && Y<Z)  //checking valid condition to avoid timer overflow
		{
			int T_period = Z - X; //Time period from input capture

            freq= F_CPU/T_period; //Main logic: Defining range using this found frequency

            clear(PORTB,6);
            clear(PORTB,5);
            
            if(freq>600 && freq<800 ){  //Green LED
                set(PORTB,7);
                clear(PORTB,6);
                clear(PORTB,5);
            }
            else if(freq>20 && freq<30){ //Red LED  
                clear(PORTB,7);
                set(PORTB,6);
                clear(PORTB,5);
            }
            else if(freq>150 && freq<300){ //Blue LED          
                clear(PORTB,7);
                clear(PORTB,6);
                set(PORTB,5);
            }
            else{       // Out of range frequency (all LEDs OFF)
                clear(PORTB,7);
                clear(PORTB,6);
                clear(PORTB,5);
            }
			
		}
        //Additional else statement to clear all LED ports when no input signal is available (i.e. null frequency), say when a hand is kept in front of the IR LED
        else{
            clear(PORTB,7); 
            clear(PORTB,6);
            clear(PORTB,5);
        }
        
        m_usb_tx_uint(freq);
        m_usb_tx_string("\n");

        clear(PORTB,7);
        clear(PORTB,6);
        clear(PORTB,5);
       
    }

    return 0;
}