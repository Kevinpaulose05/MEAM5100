/* Name: main.c
 * Author: Kevin Paulose
 */

#include "MEAM_general.h" 

//heartbeat step counter
void heartbeat(int div) 
{
    for(int i=0; i<=255;i++) // brightness increment steps from 0 to 100 intensity
    {
        OCR3A = i/div;  // dividing intensity
        _delay_ms((0.1 /255) *1000);
    }

    for(int i =255;i>=0;i--) // brightness decrement steps from 100 to 0 intensity
    {
        OCR3A =i/div;  // dividing intensity
        _delay_ms((0.4 /255) *1000);  
    }
    for(int i=0; i<=127;i++)  // brightness increment steps from 0 to 50 intensity
    {
        OCR3A = i/div; // dividing intensity
        _delay_ms((0.1 /127) *1000); 
    }
     for(int i =127;i>=0;i--) // brightness decrement steps from 50 to 0 intensity
    {
        OCR3A =i/div;  // dividing intensity
        _delay_ms((0.4 /127) *1000); 
    }
    _delay_ms(2000); 
}

int main(void)
{   
    DDRC |= 0x40; // port C6 as output set pin C6 as aoutput pin 
    
    //set prescaler /64
        // clear(TCCR3B,CS32);     
        set(TCCR3B,CS31);       
        set(TCCR3B,CS30);

    //for time mode 5
        set(TCCR3B,WGM32);    
        set(TCCR3A,WGM30);    
        // clear(TCCR3B,WGM33);   
        // clear(TCCR3A,WGM31);
   
    //to clear OCR3A and set at rollover
        set(TCCR3A,COM3A1);    
        // clear(TCCR3A,COM3A0);
    
 for(;;)
 {
    for(int i=1; i<=20;i++) //the beat should fade in 20 steps 
    {
        heartbeat(j); //function calling 
    }
 }
 return 0;

}