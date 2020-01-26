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
enum counts {startState,init,led,waitPress} count;
unsigned char op = 0x00;
unsigned char check = 0x00;
unsigned char num = 0x00;
void tick(){
 switch(count){ 			//Transitions
	case startState:		//Initial transition
	    count = init;
	    PORTC = 0x00;
	break;
	
	case init:
	  if(op==0x01){	//PA0 button pressed
	    count = led; break;
          }else{
	    count = init; break;
          }

	case led:
	    count = waitPress;
	break;
	 
	case waitPress:
	  if(op==0x01){      //button pressed
            count = waitPress; break;
	  }else if(op==0){
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

	case led:
	   if(PORTC==0){
	     PORTC = 0x01; break;
	   }else if((PORTC > 0)&&(!check)){
	     PORTC = PORTC << 1;
	     num++; 
	     if(num==0x07){
		check = 0x01;
		num = num + 0x01;
	     }
	   }else if(check){
	     PORTC = PORTC >>1;
	     num--;
	     if(num==0){
		check = 0;
	     } 
	   }
	   break;

	case waitPress:
	break;

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
	op = ~PINA & 0x01;  
	tick(); 
    }
    return 1;
}
