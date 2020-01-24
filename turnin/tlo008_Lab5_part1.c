/*	Author: Macbook
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;    
    unsigned char fuelLevel = 0x00; 
    unsigned char led = 0x00;
    /* Insert your solution below */
    while (1) {
	fuelLevel = ~PINA;
	if(fuelLevel==0x00){
	  led = ((led & 0x10) | 0x40);
	}else if((fuelLevel<=0x02)&&(fuelLevel!=0x00)){
	  led = ((led & 0x10) | 0x60);
	}else if((fuelLevel<=0x04)&&(fuelLevel>0x02)){
	  led = ((led & 0x10) | 0x70);
	}else if((fuelLevel<=0x06)&&(fuelLevel>0x04)){
	  led = ((led & 0x10) | 0x38);
	}else if((fuelLevel<=0x09)&&(fuelLevel>0x06)){
	  led = ((led & 0x10) | 0x3C);
	}else if((fuelLevel<=0x0C)&&(fuelLevel>0x09)){
	  led = ((led & 0x10) | 0x3E);
	}else if((fuelLevel<=0x0F)&&(fuelLevel>0x0C)){
	  led = ((led & 0x10) | 0x3F);
	}	
	PORTC = led;
	led = 0x00;
        fuelLevel = 0x00;
    }
    return 1;
}
