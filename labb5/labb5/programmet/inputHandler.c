/*
 * inputHandler.c
 *
 * Created: 2022-05-04 11:06:34
 *  Author: 
 */ 

#include "inputHandler.h"

void input(IH *self) {
	// ?????
	while (!(UCSR0A & (1 << RXC0)));
	volatile uint8_t indata = UDR0; // does it have to be volatile?
		
	if (indata & nCar) {
		ASYNC(self->controller, newCarInQueue, 1); // Adding to the northbound queue
	} else if (indata & nBridge) {
		ASYNC(self->controller, newCarOnBridge, 1); // Adding a car on the bridge towards north
	} else if (indata & sCar) {
		ASYNC(self->controller, newCarInQueue, 2); // Adding to the southbound queue
	} else if (indata & sBridge) {
		ASYNC(self->controller, newCarOnBridge, 2); // Adding a car on the bridge towards south
	}
}