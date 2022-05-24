/*
 * UserInterface.h
 *
 * Created: 2022-05-23 18:57:19
 *  Author: 
 */ 


#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "TinyTimber.h"

typedef struct UserInterface_s {
	Object super;
} UserInterface;

#define initUserInterface() { initObject() }
	
#define AsyncNormalUBRREquation (8000000/16/9600-1)
	
void initUI(UserInterface *self);
void writeChar(char ch, int pos);
void printAt(int pos, int val);
void updateOutput(UserInterface *self, int *queues);

#endif /* USERINTERFACE_H_ */