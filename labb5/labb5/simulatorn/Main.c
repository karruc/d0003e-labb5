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
	printf("Hi!");
	
	// Initialize everything in the simulator
	initProgram();
	initUserInterface();
	initControllerInterface();
	
	// Our threads.
	pthread_t userInputThread;
	pthread_t atBridgeThread;
	pthread_t onBridgeThread;
	pthread_t controllerInterfaceThread;
	
	// Starts our threads.
	pthread_create(&userInputThread, NULL, userInput, NULL);
	pthread_create(&atBridgeThread, NULL, atBridgeManager, NULL);
	pthread_create(&onBridgeThread, NULL, onBridgeManager, NULL);
	pthread_create(&controllerInterfaceThread, NULL, readPort, NULL);
	
	// Makes your current thread join into the selected thread.
	pthread_join(userInputThread, NULL);	
}