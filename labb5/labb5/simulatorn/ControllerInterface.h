

#ifndef CONTROLLERINTERFACE_H_
#define CONTROLLERINTERFACE_H_


extern pthread_mutex_t controllerInterfaceMutex; // Mutex for everything within ControllerInterface
extern int port;
extern struct termios portSettings;

extern void initControllerInterface(void);
extern void *readPort(void *arg);
extern void atBridgeCI(int direction);
void onBridgeCI(int lightStatus);

#endif /* CONTROLLERINTERFACE_H_ */
