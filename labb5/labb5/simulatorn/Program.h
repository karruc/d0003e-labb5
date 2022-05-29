
#ifndef PROGRAM_H_
#define PROGRAM_H_


#include "ControllerInterface.h"


#define BOTHRED 0
#define GREENTONORTH 1
#define GREENTOSOUTH 2

#define B 0 // amount of people on the bridge
#define N 1 // amount of cars in queue towards north
#define S 2 // amount of cars in queue towards south

extern sem_t atBridgeSem; // Semaphore for a car that just arrived at the bridge
extern sem_t onBridgeSem; // Semaphore for a car that just got on the bridge
extern pthread_mutex_t programMutex; // Mutex for everything within Program
extern int lightStatus;
extern int queues[3];
extern int direction;

extern void initProgram(void);
extern void *onBridge(void *arg);
extern void *onBridgeManager(void *arg);
extern void setLightStatus(int _lightStatus);
extern void addCar(int _direction);

#endif /* PROGRAM_H_ */
