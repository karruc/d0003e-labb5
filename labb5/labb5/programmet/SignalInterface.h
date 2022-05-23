/*
 * SignalInterface.h
 *
 * Created: 2022-05-23 18:57:47
 *  Author: 
 */ 


#ifndef SIGNALINTERFACE_H_
#define SIGNALINTERFACE_H_

#include "TinyTimber.h"

struct UserInterface_s;
typedef struct UserInterface_s UserInterface;

struct Program;
typedef struct Program_s Program;

typedef struct SignalInterface_s {
	Object super;
	UserInterface *ui;
	Program *program;
} SignalInterface;

#define initSignalInterface(ui, pr){initObject(), ui, pr}

#define nCar (1<<0)
#define nBridge (1<<1)
#define sCar (1<<2)
#define sBridge (1<<3)

void triggerOnSignal(SignalInterface *self);
void sendLightSignal(SignalInterface *self, int lightSignal);

#endif /* SIGNALINTERFACE_H_ */