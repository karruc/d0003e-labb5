/*
 * ControllerInterface.c
 *
 * Created: 2022-05-11 14:17:35
 *  Author:
 */ 

#include "CommonLibraries.h"
#include "ControllerInterface.h"
#include "Program.h"


pthread_mutex_t controllerInterfaceMutex;
int port;
struct termios portSettings;

void initControllerInterface(void) {	
	
	pthread_mutex_init(&controllerInterfaceMutex, NULL);
	
	// Settings for the port that we are communicating with.
	port = open("/dev/ttyS0", O_RDWR);
	
	tcgetattr(port, &portSettings);
	fcntl(port, F_SETFL, O_NONBLOCK);
	cfsetospeed(&portSettings, B9600); // "serial port speed of 9600bps"
	cfsetispeed(&portSettings, B9600); // "serial port speed of 9600bps"
	
	portSettings.c_cflag &= ~CSIZE; 	// ?? Clear char size
	portSettings.c_cflag |= CS5;	// ?? set 5 bit char size
	portSettings.c_cflag &= ~CSTOPB; // one  stop bit
	portSettings.c_cflag &= ~PARENB; // no parity bits
	portSettings.c_cflag |= CREAD;	// ?? Enable receive
	portSettings.c_cc[VMIN] =  1; // ?? Read at least 1 char
}
	
void *readPort(void *arg) {
	uint8_t readFromPort; // Cause the port must be used with 8 bits words
	while (true)
	{
		readFromPort = 0;
		pthread_mutex_lock(&controllerInterfaceMutex);
		read(port, &readFromPort, 1);
		pthread_mutex_unlock(&controllerInterfaceMutex);
		
		// printf("Data: '%d'\n", readFromPort);
		
		if (readFromPort == 0b1010) {
			setLightStatus(BOTHRED);
		} else if (readFromPort == 0b1001) {			
			setLightStatus(GREENTONORTH);
			sem_post(&onBridgeSem);	// A car is moving from "at the bridge" to "on the bridge"
		} else if (readFromPort == 0b0110) {
			setLightStatus(GREENTOSOUTH);
			sem_post(&onBridgeSem);	// A car is moving from "at the bridge" to "on the bridge"
		}
	}
}

void atBridgeCI(int direction) {
	uint8_t toWriteToPort; // Cause the port must be used with 8 bits words
	if (direction == N) {
		toWriteToPort = 0b0001;
	} else if (direction == S) {
		toWriteToPort = 0b0100;
	}
	pthread_mutex_lock(&controllerInterfaceMutex);
	write(port, &toWriteToPort, 1);
	pthread_mutex_unlock(&controllerInterfaceMutex);
}

void onBridgeCI(int lightStatus) {
	uint8_t toWrite;
	if (lightStatus == GREENTONORTH) {
		toWrite = 0b0010;
	} else if (lightStatus == GREENTOSOUTH) {
		toWrite = 0b1000;
	}
	pthread_mutex_lock(&controllerInterfaceMutex);
	write(port, &toWrite, 1);
	pthread_mutex_unlock(&controllerInterfaceMutex);
}

// call to program?