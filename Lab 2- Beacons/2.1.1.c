/* Name: main.c
 * Author: Kevin Paulose
 * Code for: 2.1.1
 */

#include "MEAM_general.h"

int main()
{
 clear(DDRC,7); // PC7 input
 set(DDRB,3);  // PB3 output
 
 for (;;) 
 {
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