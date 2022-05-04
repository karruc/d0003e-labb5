/*
 * controller.h
 *
 * Created: 2022-05-04 11:07:53
 *  Author: 
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#ifndef CARS_H_
#define CARS_H_

#include "TinyTimber.h"
#include <avr/io.h>
#include "outputHandler.h"
#include "GUI.h"

#define maxTrough 4

//Directions and bridge
#define B 0
#define N 1
#define S 2


#define RED 0
/*
#define NORTHGREEN 1
#define SOUTHGREEN 2
*/

typedef struct {
	Object super; 
	int queue[3];
	int bridgeDirection;
	int lights;
	int carsPassed;
	OutputHandler *OpH;
	GUI *gui;
	}Controller;

#define initController(OH, gui){initObject(),{0, 0, 0}, 0, 0, 0, OH, gui}

// Queue
void newQueue(Controller *self, int dir);
void decQueue(Controller *self, int dir);

// Bridge
void newBridge(Controller *self, int dir);
void decBridge(Controller *self);


// Functions to control the traffic lights
void redLight(Controller *self);
void greenLight(Controller *self, int dir);
void nLights(Controller *self);
void sLights(Controller *self);

// Init queues and lights
void init(Controller *self);

#endif /* CONTROLLER_H_ */