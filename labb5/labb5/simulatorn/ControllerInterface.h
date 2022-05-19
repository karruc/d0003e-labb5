/*
 * ControllerInterface.h
 *
 * Created: 2022-05-11 14:18:18
 *  Author: 
 */ 


#ifndef CONTROLLERINTERFACE_H_
#define CONTROLLERINTERFACE_H_


extern pthread_mutex_t controllerInterfaceMutex; // Mutex for everything within ControllerInterface
extern int port;
extern struct termios portSettings;

extern void initControllerInterface(void);
extern void *readPort(void *arg);
extern void atBridgeCI(int direction);

#endif /* CONTROLLERINTERFACE_H_ */