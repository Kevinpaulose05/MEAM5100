/* Name: main.c (3.2.3)
 * Author: Kevin Paulose
 * Description: Final Waldo code that integrates input sensing side to output side
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

void setPWMchannel(int ch) //Set PWM channel only for the three pins used
    if (ch == 1)
    {
        set(DDRC, 6); // set PIN C6 as output
    
        // set prescaler to /1024
        set(TCCR3B, CS30);
        clear(TCCR3B, CS31);
        set(TCCR3B, CS32); 
    
        set(TCCR3A, COM3A1); //set timer TCCR3A to COM3A1 bit (OCR3A output capture)

        //set to mode 5
        clear(TCCR3B, WGM33);
        set(TCCR3B, WGM32);
        clear(TCCR3A, WGM31);
        set(TCCR3A, WGM30);

    }
    if(ch == 4)
    {
        set(DDRB, 5); // set PIN B5 as output
        
        // set prescaler to /1024
        set(TCCR1B, CS10);
        clear(TCCR1B, CS11);
        set(TCCR1B, CS12); 
    
        set(TCCR1A, COM1A1); //set timer TCCR1A to COM1A1 bit (OCR1A output capture)

        //set to mode 5
        clear(TCCR1B, WGM13);
        set(TCCR1B, WGM12);
        clear(TCCR1A, WGM11);
        set(TCCR1A, WGM10);   
    }
    if(ch == 5)
    {
        set(DDRB, 6); // set PIN B6 as output
        
        // set prescaler to /1024
        set(TCCR1B, CS10);
        clear(TCCR1B, CS11);
        set(TCCR1B, CS12); 
    
        set(TCCR1A, COM1B1); //set timer TCCR1A to COM1B1 bit (OCR1B output capture)

        //set to mode 5
        clear(TCCR1B, WGM13);
        set(TCCR1B, WGM12);
        clear(TCCR1A, WGM11);
        set(TCCR1A, WGM10);   
    }
}

void servoMotor(int adc_value, int ch)
{
    if (ch == 1) //base joint PC6
    {
       // OCR3A = (12/(912-0)) * adc_value + 12;
        OCR3A = 0.01315*adc_value + 12;
    }
    else if (ch == 4) //elbow joint PB5
    {
        // OCR1A = (3/(930-190)) * adc_value + 21;
        OCR1A = 0.00405*adc_value + 21;
    
    }
    else if (ch == 5) //arm joint PB6
    {                                                                                              
        // OCR1B = (16/(380-0)) * adc_value + 8;
        OCR1B = 0.0421*adc_value + 8;
    }
}


int main()
{
    m_usb_init();     // initialize serial port
    _clockdivide(0);  // set clock speed to 16 MHz

    for (;;) {
        // (1) Get ADC1 reading for the base joint (PC6)
        setup_ADC(1);
        setPWMchannel(1);
        double adc1 = read_ADC();
        servoMotor(adc1, 1);

        //printing necessary ADC values in putty
        double joint1 = adc1 / 1024.0 * 180.0; // convert ADC values 0-1023 to angles 0-179 degrees
        m_usb_tx_string("\n\n\n Joint 1: ");
        m_usb_tx_int(joint1);
        m_usb_tx_int(adc1);
        _delay_ms(500);


        // (2) Get ADC4 reading for the elbow joint (PB5)
        setup_ADC(4);
        setPWMchannel(4);
        double adc2 = read_ADC();
        servoMotor(adc2, 4);
        
        double joint2 = adc2 / 1024.0 * 180.0; //printing necessary ADC values in putty
        m_usb_tx_string("\n Joint 2: ");
        m_usb_tx_int(joint2);
        m_usb_tx_int(adc2);
        _delay_ms(500);
        

        // (3) Get ADC5 reading for the arm joint (PB6)
        setup_ADC(5);
        setPWMchannel(5);
        double adc3 = read_ADC();
        servoMotor(adc3, 5);
        
        double joint3 = adc3 / 1024.0 * 180.0; //printing necessary ADC values in putty
        m_usb_tx_string("\n Joint 3: ");
        m_usb_tx_int(joint3);
        m_usb_tx_int(adc3);
        _delay_ms(1500);
    }

    return 0;
}