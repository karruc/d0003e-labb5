/*
 * controller.h
 *
 * Created: 2022-05-04 11:07:53
 *  Author: 
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "TinyTimber.h"
#include "outputHandler.h"
#include "GUI.h"
#include <avr/io.h>

#define maxTrough 10 // max 10 one direction before we switch the lights

// Directions
#define B 0 // amount of people on the bridge
#define N 1 // amount of cars in queue towards north
#define S 2 // amount of cars in queue towards south

// Light statuses
#define BOTHRED 0
#define GREENTONORTH 1
#define GREENTOSOUTH 2

typedef struct {
	Object super; 
	int queue[3];
	int brDir;
	int lights;
	int passed;
	OH *OpH;
	GUI *gui;
	}Controller;

#define initController(OH, gui){initObject(),{0, 0, 0}, 0, 0, 0, OH, gui}

// Queue
void newCarInQueue(Controller *self, int dir);
void deleteCarFromQueue(Controller *self, int dir);

// Bridge
void newCarOnBridge(Controller *self, int dir);
void deleteCarFromBridge(Controller *self);


// Functions to control the traffic lights
void redLight(Controller *self);
void greenLight(Controller *self, int dir);
void nLights(Controller *self);
void sLights(Controller *self);

// Init queues and lights
void startController(Controller *self);

#endif /* CONTROLLER_H_ */