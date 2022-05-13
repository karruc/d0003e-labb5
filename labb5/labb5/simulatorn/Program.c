/*
 * Program.c
 *
 * Created: 2022-05-11 14:18:50
 *  Author:
 */ 
#include "Program.h"

void initProgram(void) {
	sem_init(&atBridgeSem, 0, 0); // Initialize the semaphore for the queue at the bridge
	sem_init(&onBridgeSem, 0, 0); // Initialize the semaphore for getting on the bridge
	
	// Informing the user about an error with initializing mutex for the program
	// Evaluate the necessity of this.
	if (pthread_mutex_init(&programMutex, NULL) != 0) {
		printf("Error during initializing mutex for the program");
	}
	
	lightStatus = BOTHRED;	
}

void atBridge(int direction) {
	pthread_mutex_lock(&programMutex);
	queues[direction]++;
	pthread_mutex_unlock(&programMutex);
}

void atBridgeManager(void) {
	while(true) {
		sem_wait(&atBridgeSem);
		atBridge(direction);
	}
}

void onBridge(void) {
	pthread_mutex_lock(&programMutex);
	if(queues[lightStatus] <= 0) {
		pthread_mutex_unlock(&programMutex);
	} else {
		queues[lightStatus]--;
		queues[0]++; // ???
		pthread_mutex_unlock(&programMutex);
		sleep(5); // Time it takes for the car to pass
		pthread_mutex_lock(&programMutex);
		queues[0]--;
	}
}

void onBridgeManager(void) {
	while(true) {
		sem_wait(&onBridgeSem);
		pthread_t newCar;
		
		// Evaluate the necessity of this.
		if(pthread_create(&newCar, NULL, onBridge, NULL)) {
			printf("Error during creating a thread for a new car");
		}
	}
}