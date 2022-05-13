/*
 * Program.c
 *
 * Created: 2022-05-11 14:18:50
 *  Author: k&j
 */ 
#include "Program.h"

void initProgram(void) {
	sem_init(&arrivedSem, 0, 0); // Initialize the semaphore for arrival
	sem_init(&onBridgeSem, 0, 0); // Initialize the semaphore for getting on the bridge
	
	// Informing the user about an error with initializing mutex for the program
	if (pthread_mutex_init(&programMutex, NULL) != 0) {
		printf("Error during initializing mutex for the program");
	}
	
	lightStatus = BOTHRED;	
}



		
// need arrival here that does these:
	//Update queues
	pthread_mutex_lock(&stateMutex);
	queues[dir]++;
	pthread_mutex_unlock(&stateMutex);
	print();
	
// some shit called arrival manager, call it MANAGER cause its a continual thread and it will have arrivalWait basically

// as above, but this time a bridge manager, *bridgeEnter in the code.
// in the two of the above it MIGHT work to skip the *pointer in method declaration and then while using them just use a &reference

// put carOnBridge here as well ofc

