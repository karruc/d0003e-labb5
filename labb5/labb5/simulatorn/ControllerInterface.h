/*
 * ControllerInterface.h
 *
 * Created: 2022-05-11 14:18:18
 *  Author: 
 */ 


#ifndef CONTROLLERINTERFACE_H_
#define CONTROLLERINTERFACE_H_

#include "Program.h"

#include <termios.h>
#include <fcntl.h>
#include <stdint.h>

pthread_mutex_t controllerInterfaceMutex; // Mutex for everything within ControllerInterface
int port;
static struct termios portSettings;

void initControllerInterface(void);
void readPort(void);
void atBridgeCI(int direction);

#endif /* CONTROLLERINTERFACE_H_ */