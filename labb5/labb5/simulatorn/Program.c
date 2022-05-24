/*
 * Program.c
 *
 * Created: 2022-05-11 14:18:50
 *  Author:
 */ 

#include "CommonLibraries.h"
#include "Program.h"

sem_t atBridgeSem; // Semaphore for a car that just arrived at the bridge
sem_t onBridgeSem; // Semaphore for a car that just got on the bridge
pthread_mutex_t programMutex; // Mutex for everything within Program
int lightStatus;
int queues[3];
int direction;

void initProgram(void) {
	sem_init(&onBridgeSem, 0, 0); // Initialize the semaphore for getting on the bridge
	
	pthread_mutex_init(&programMutex, NULL);
	
	lightStatus = BOTHRED;
}

void *onBridge(void *arg) {
	pthread_mutex_lock(&programMutex);
	if(queues[lightStatus] <= 0) {
		pthread_mutex_unlock(&programMutex);
	} else {
		queues[lightStatus]--;
		queues[0]++; // ???
		pthread_mutex_unlock(&programMutex);
		
		onBridgeCI(lightStatus);
		sleep(5); // Time it takes for the car to pass
		
		pthread_mutex_lock(&programMutex);
		queues[0]--;
		pthread_mutex_unlock(&programMutex);
	}
}

void *onBridgeManager(void *arg) {
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
	//printf("New light status set: '%d'", _lightStatus);
}

void addCar(int _direction) {	
	pthread_mutex_lock(&programMutex);
	queues[_direction]++;
	pthread_mutex_unlock(&programMutex);
	atBridgeCI(_direction);
}