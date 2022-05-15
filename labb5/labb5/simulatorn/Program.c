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
		pthread_mutex_unlock(&programMutex);
	}
}

void onBridgeManager(void) {
	while(true) {
		sem_wait(&onBridgeSem);
		pthread_t newCar;
		pthread_create(&newCar, NULL, onBridge, NULL);
	}
}

void setLightStatus(int _lightStatus) {
	pthread_mutex_lock(&programMutex);
	lightStatus = _lightStatus;
	pthread_mutex_unlock(&programMutex);
}

void setDirection(int _direction) {	
	pthread_mutex_lock(&programMutex);
	direction = _direction;
	pthread_mutex_unlock(&programMutex);
}