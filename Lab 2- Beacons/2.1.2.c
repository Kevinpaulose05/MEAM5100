/* Name: main.c
 * Author: Kevin Paulose
 * Code for: 2.1.2
 */

#include "MEAM_general.h"
#include "m_usb.h"
#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10); m_usb_tx_char(13)

void checkPC7() 
{
int oldState; // To remember the previous state of PC7
int pinState = bit_is_set(PINC,7);  // Read and store the current state of PC7

if (pinState != oldState) // If there's a change in pin state, print the timestamp 
  {
    m_usb_tx_string("\ntime- ");
    m_usb_tx_int(TCNT3);
  }
  
  oldState = pinState; // Update the old state to match the current pin state
}

int main()
{
  m_usb_init();

  // Set timer prescaler for timer counter 3 (TCCR3B) to divide the clock /1024
  set(TCCR3B,CS30);
  set(TCCR3B,CS32);
  
  clear(DDRC,7); //PC7 input
  set(DDRB,3); //PB3 output

  for(;;)
  {
    checkPC7();

    if (bit_is_set(PINC, 7))   
    {
      set(PORTB,3);
    }  

    else
    {
    clear(PORTB,3);
    }
  }
}

