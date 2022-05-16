/*
 * UserInterface.h
 *
 * Created: 2022-05-11 14:16:57
 *  Author:
 */ 


#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "Program.h"
#include <stdio.h>

void initUserInterface(void);
void *userInput(void *arg);
void printInTerminal(void);

static struct termios programSettings;

#endif /* USERINTERFACE_H_ */