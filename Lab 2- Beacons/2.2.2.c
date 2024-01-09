/* Name: main.c
 * Author: Kevin Paulose
 * Code for: 2.2.2
 */

#include "MEAM_general.h"
#include "m_usb.h"

#define PRINTNUM(x) m_usb_tx_uint(x); m_usb_tx_char(10); m_usb_tx_char(13)

int main()
{
  m_usb_init();
  DDRC = 0x00;  // Configures all pins of port C as input
  DDRB = 0xFF;  // Configures all pins of port B as output
  
  for (;;){
    if (bit_is_set(PINC,7))   //PC7 is checked if it is high or low
    {
      m_usb_tx_uint(bit_is_set(PINC,7));    // Send input bit status (0 or 1) to USB output
      set(PORTB,3);     // Set PB3 high to turn on LED
    }
    else
    {
      m_usb_tx_uint(bit_is_set(PINC,7));
      clear(PORTB,3); //Clear PB3 to turn off LED
    }
  }

  return 0;
}