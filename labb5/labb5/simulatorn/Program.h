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


sem_t atBridgeSem; // Semaphore for a car that just arrived at the bridge
sem_t onBridgeSem; // Semaphore for a car that just got on the bridge
pthread_mutex_t programMutex; // Mutex for everything within Program
int lightStatus;
int queues[3];
int direction;

void initProgram(void);
void atBridge(int direction);
void atBridgeManager(void);
void onBridge(void);
void onBridgeManager(void);

#endif /* PROGRAM_H_ */