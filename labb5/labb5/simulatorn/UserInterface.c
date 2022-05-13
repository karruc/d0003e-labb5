/*
 * UserInterface.c
 *
 * Created: 2022-05-11 14:16:33
 *  Author:
 */
#include "UserInterface.h"

// ??? GO THROUGH THIS, UNDERSTAND THIS AND FIX COMMENTS
void initUserInterface(void) {
	//copy current settings
	tcgetattr(STDIN_FILENO, &prgmTerminalSettings);

	//set new settings
	prgmTerminalSettings.c_lflag &= ~(ICANON) // Disable input buffer until endl or EOF
	&  ~(ECHO);  // Don't echo back typed keys
		
	//Save new settings
	tcsetattr(STDIN_FILENO, TCSANOW, &prgmTerminalSettings);
}

void userInput(char ch) {
	while(ch!='e') {
		if(ch=='n') {
			pthread_mutex_lock(&programMutex);
			direction = N;
			pthread_mutex_unlock(&programMutex);
			sem_post(&atBridgeSem);
		} else if(ch=='s') {
			pthread_mutex_lock(&programMutex);
			direction = S;
			pthread_mutex_unlock(&programMutex);
			sem_post(&atBridgeSem);
		}
		print("Bye!");
	}
}

void printInTerminal(void) {
	pthread_mutex_lock(&programMutex);
	if (lightStatus==BOTHRED) {
		printf("Both lights are red!\n");
	} else if(lightStatus==GREENTONORTH) {
		printf("Light to north: green!\nLight to south: red!");	
	} else {
		printf("Light to north: red!\nLight to south: green!");
	}
	printf("On the bridge: %d,\nat the bridge north: %d,\nat the bridge south: %d", queues[0], queues[1], queues[2]);
	pthread_mutex_unlock(&programMutex);
}