/*
 * Program.h
 *
 * Created: 2022-05-11 14:19:00
 *  Author:
 */ 


#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "ControllerInterface.h"

#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>



sem_t atBridgeSem; // Semaphore for a car that just arrived at the bridge
sem_t onBridgeSem; // Semaphore for a car that just got on the bridge
pthread_mutex_t programMutex; // Mutex for everything within Program
int lightStatus;
int queues[3];
int direction;

// Directions
#define B 0 // amount of people on the bridge
#define N 1 // amount of cars in queue towards north
#define S 2 // amount of cars in queue towards south

// Light statuses
#define BOTHRED 0
#define GREENTONORTH 1
#define GREENTOSOUTH 2

void initProgram(void);
void atBridge(int direction);
void *atBridgeManager(void *arg);
void *onBridge(void *arg);
void *onBridgeManager(void *arg);
void setLightStatus(int _lightStatus);
void setDirection(int _direction);

#endif /* PROGRAM_H_ */