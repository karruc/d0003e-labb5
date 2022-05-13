/*
 * UserInterface.c
 *
 * Created: 2022-05-11 14:16:33
 *  Author:
 */
#include "UserInterface.h"

void userInput(char ch) {
	while(ch!='e') {
		if(ch=='n') {
			pthread_mutex_lock(&programMutex);
			dir
		}
	}
}

void *keyboardInput(void *arg){
	char ch;
	
	while ( (ch = getchar()) != 'e'){
		if(ch == 's'){
			
			// call this bullshitbelow method south and it will be IN PROGRAM and we call it here
			pthread_mutex_lock(&stateMutex);
			//Set direction of car entering queue
			arrivalDir = SOUTH;
			pthread_mutex_unlock(&stateMutex);
			//Allow one car to enter the queue
			sem_post(&arrivalSem);
		}
		else if(ch == 'n'){
			// call this bullshitbelow method north and it will be IN PROGRAM and we call it here
			pthread_mutex_lock(&stateMutex);
			//Set direction of car entering queue
			arrivalDir = NORTH;
			pthread_mutex_unlock(&stateMutex);
			//Allow one car to enter the queue
			sem_post(&arrivalSem);
		}
	}
	print();
	printf("Exits the Simulator\n");
}

// remember to put everything from GUI here as well