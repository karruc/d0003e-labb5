/*
 * SignalInterface.c
 *
 * Created: 2022-05-23 18:57:59
 *  Author: 
 */ 

#include "CommonLibraries.h"
#include "SignalInterface.h"
#include "TinyTimber.h"
#include "UserInterface.h"
#include "Program.h"

// Signal in
void triggerOnSignal(SignalInterface *self) {
	
	while (!(UCSR0A & (1 << RXC0)));
	volatile uint8_t indata = UDR0;
	
	if (indata & nCar) {
		ASYNC(self->program, addCarQueue, N); // Adding to the northbound queue
	} else if (indata & nBridge) {
		ASYNC(self->program, addCarBridge, N); // Adding a car on the bridge towards north
	} else if (indata & sCar) {
		ASYNC(self->program, addCarQueue, S); // Adding to the southbound queue
	} else if (indata & sBridge) {
		ASYNC(self->program, addCarBridge, S); // Adding a car on the bridge towards south
	}
}

// Signal out
void sendLightSignal(SignalInterface *self, int lightSignal) {
	int signalToSend =	(lightSignal == 0) ? 0xA : // Both lights are red - cannot go
						(lightSignal == 1) ? 0x9 : // Northbound light is green (on), southbound is red (off)
						(lightSignal == 2) ? 0x6 : // Northbound light is red (off), southbound is green (on)
											 0; // Default value 0

	while(!(UCSR0A & (1 << UDRE0))); // Wait
	UDR0 = signalToSend;
}