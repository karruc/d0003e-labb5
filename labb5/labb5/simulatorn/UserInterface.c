/*
 * UserInterface.c
 *
 * Created: 2022-05-11 14:16:33
 *  Author:
 */

#include "CommonLibraries.h"
#include "UserInterface.h"
#include "Program.h"


void initUserInterface(void) {
	struct termios programSettings;
	tcgetattr(STDIN_FILENO, &programSettings);
	programSettings.c_lflag &= ~( ICANON | ECHO); // Don't echo back typed keys		
	tcsetattr(STDIN_FILENO, TCSANOW, &programSettings);
}

void *userInput(void *arg) {
	char ch;
	while(ch = getchar()) {
		if (ch == 'e') {
			break;
		} else if (ch == 'n') {
			addCar(N);
		} else if (ch == 's') {
			addCar(S);
		}
	}
}

void *infoOutput(void *arg) {
	while(true) {
		sleep(1);
		printInTerminal();
	}
}

void printInTerminal(void) {
	pthread_mutex_lock(&programMutex);
	
	char* statusString;
	if (lightStatus == BOTHRED) {
		statusString = "Both lights are red!";
	} else if(lightStatus == GREENTONORTH) {
		statusString = "Light to north: green!\nLight to south: red!";	
	} else {
		statusString = "Light to north: red!\nLight to south: green!";
	}
	
	printf("Queue count: [N: %d, _: %d, S: %d] Light status: %s\r", queues[1], queues[0], queues[2], statusString);
	pthread_mutex_unlock(&programMutex);
}