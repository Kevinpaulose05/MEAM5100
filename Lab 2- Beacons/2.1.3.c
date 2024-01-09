/* Name: main.c
 * Author: Kevin Paulose
 * Code for: 2.1.3
 */

#include "MEAM_general.h"
#include "m_usb.h"

unsigned int oldTime, T_period;

void floatNum(float timer) // Function to print a floating-point number (timer) to USB output
{
  m_usb_tx_uint(timer); // Send value to the USB output
}

// Function to check input capture flag and calculate time between each press-depress
void checkPC7()
{
  while (!bit_is_set(TIFR3,ICF3)); // Wait until the Input Capture Flag (ICF3) in Timer 3 (TIFR3) is set
  set(TIFR3,ICF3); // Clear flag by writing 1 to the flag bit

  // Calculate the time period between each press-depress
  T_period = ICR3 - oldTime; //time between a press-depress
  oldTime = ICR3; //update time

  float time = T_period*4.2*1000/65535; // prescaler /1024 and time is in seconds
  // timer 1,3 have 16bit register (counts to 65535)
  //@16Mz max value corresponds to 4.2seconds

  floatNum(time);
}
int main(void)
{
  m_usb_init();

  // Configure Timer 3 (TCNT3) with a /1024 prescaler
  set(TCCR3B,CS32);
  clear(TCCR3B,CS31);
  set(TCCR3B,CS30);

  // Configure Timer 3 (TCNT3) for normal mode (up to 0xFFFF, 16-bit)
  clear(TCCR3B, WGM33);
  clear(TCCR3B, WGM32);
  clear(TCCR3B, WGM31);
  clear(TCCR3B, WGM30);

  // Set Input Capture Edge Select (ICES3) to store timer value on falling edge
  set(TCCR3B,ICES3);
  
  for (;;){
  m_usb_tx_string("\nmash: ");
  checkPC7(); // Print the mashing timestamps
  }

  return 0;
}



