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


sem_t arrivedSem; // Semaphore for a car that just arrived
sem_t onBridgeSem; // Semaphore for a car that just got on the bridge
pthread_mutex_t programMutex; // Mutex for everything within Program
int lightStatus 


#endif /* PROGRAM_H_ */