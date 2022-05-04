/*
 * outputHandler.c
 *
 * Created: 2022-05-04 11:07:07
 *  Author: 
 */ 

#include "outputHandler.h"

void lightsOut(OH *self, int lightsOn) {
	// Stores a value to be sent further to the simulator
	int lightStatus = 0;
	
	//3 combinations for the two traffic lights:
	if (lightsOn == 0){ // Both lights are red - cannot go
		lightStatus = 0xA;
	}
	else if (lightsOn == 1){ // Northbound light is green (on), southbound is red (off)
		lightStatus = 0x9;
	}
	else if (lightsOn == 2){ // Northbound light is red (off), southbound is green (on)
		lightStatus = 0x6;
	}
	
	// ...
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = lightStatus;
	
}