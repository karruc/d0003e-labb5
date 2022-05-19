/*
 * main.c
 *
 * Created: 2022-05-04 11:09:26
 *  Author: 
 */ 

#include "CommonLibraries.h"
#include "Program.h"
#include "ControllerInterface.h"
#include "UserInterface.h"

int main(void) {
	printf("Hi!\n");

	// Initialize everything in the simulator
	initProgram();
	initUserInterface();
	initControllerInterface();
	
	// Our threads.
	pthread_t infoOutputThread;
	pthread_t onBridgeThread;
	pthread_t controllerInterfaceThread;
	pthread_t userInputThread;
	
	// Starts our threads.
	pthread_create(&infoOutputThread, NULL, infoOutput, NULL);
	pthread_create(&onBridgeThread, NULL, onBridgeManager, NULL);
	pthread_create(&controllerInterfaceThread, NULL, readPort, NULL);
	pthread_create(&userInputThread, NULL, userInput, NULL);
	
	// Makes your current thread join into the selected thread.
	pthread_join(userInputThread, NULL);
	
	printf("\nBye!");
}