/*
 * main.c
 *
 * Created: 2022-05-04 11:09:26
 *  Author: 
 */ 
#include "Program.h"
#include "UserInterface.h"
#include "ControllerInterface.h"

int main(void) {
	print("Hi!");
	
	// Initialize everything in the simulator
	initProgram();
	initUserInterface();
	initControllerInterface();
	
	// Our threads. Do we need them all tho? 
	pthread_t userInputThread;
	pthread_t atBridgeThread;
	pthread_t onBridgeThread;
	pthread_t controllerInterfaceThread;
	
	// What is this?
	//pthread_join(userInputThread, NULL);	
}