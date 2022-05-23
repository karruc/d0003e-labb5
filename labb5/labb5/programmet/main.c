/*
 * labb5.c
 *
 * Created: 2022-05-04 11:04:48
 * Author : 
 */ 
#include "CommonLibraries.h"
#include "UserInterface.h"
#include "SignalInterface.h"
#include "Program.h"

int main(void) {
	
	UserInterface ui = initUserInterface();
	SignalInterface si = initSignalInterface(&ui, NULL);
	Program p = initProgram(&si, &ui);
	
	si.program = &p;
	
	INSTALL (&si, &triggerOnSignal, IRQ_USART0_RX);
	return TINYTIMBER(&p, startProgram, NULL);

}

