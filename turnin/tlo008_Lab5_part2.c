/*	Author: Tsz Hin Lo (Chris)
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
enum counts {startState,init,waitPress,inc,dec,reset} count;
unsigned char op = 0x00;

void tick(){
 switch(count){ 			//Transitions
	case startState:		//Initial transition
	    count = init;
	    PORTC = 0x07;
	break;
	
	case init:
	  if(op==0x03){
	    count = reset; break;
	  }else if(op==0x01){	//PA0 button pressed
	    count = inc; break;
	  }else if(op==0x02){ //PA0 button pressed
	    count = dec; break;
	  }else{
	    count = init; break;
	  }

	case inc:
            count = waitPress;
	break;

	case dec:
            count = waitPress;
	break;

	case waitPress:
          if(op==0x03){
	    count = reset; break;
	  }else if((op==0x01)||(op==0x02)){      //button pressed
            count = waitPress; break;
	  }else{
            count = init; break;
          }	
	
	case reset:
	if((op==0x01)||(op==0x02)){      //button pressed
            count = reset; break;
          }else{
            count = init; break;
          }

	default:
	break;
 }
 switch(count){

	case startState:
	break;	

	case init:
	break;

	case inc:
	 if(PORTC<0x09){
	   PORTC = PORTC + 0x01; break;
	 }else{
	   PORTC = 0x09; break;
	 }

	case dec:
         if(PORTC>0x00){
           PORTC = PORTC - 0x01; break;
         }else{
           PORTC = 0x00; break;
         }
	
	case waitPress:
	break;

	case reset:
	   PORTC = 0x00; break;

	default:
	break;
 }
}


int main(void) {
    /* Insert DDR and PORT initializations */
    	DDRA = 0x00 ; PORTA = 0xFF;
	DDRC = 0xFF ; PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	op = PINA & 0x03;  
	tick(); 
    }
    return 1;
}
