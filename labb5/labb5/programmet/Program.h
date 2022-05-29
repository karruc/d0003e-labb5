
#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "TinyTimber.h"

struct SignalInterface_s;
typedef struct SignalInterface_s SignalInterface;

struct UserInterface_s;
typedef struct UserInterface_s UserInterface;

typedef struct Program_s {
	Object super;
	SignalInterface *si;
	UserInterface *ui;
	int carQueues[3]; // north, south and on the bridge = 3 queues
	int lightDirection;
	int travelDirection;
	int carsSinceLightSwitch;
} Program;

#define initProgram(si, ui){initObject(), si, ui, {0, 0, 0}, 0, 0, 0}

#define maxTrough 5 // max 10 one direction before we switch the lights

// Directions
#define B 0 // amount of cars on the bridge
#define N 1 // amount of cars in queue towards north
#define S 2 // amount of cars in queue towards south

// Light statuses
#define BOTHRED 0
#define GREENTONORTH 1
#define GREENTOSOUTH 2

// Init queues and lights
void startProgram(Program *self);

// Handle car movement
void addCarBridge(Program *self, int dir);
void addCarQueue(Program *self, int dir);
void deleteCarBridge(Program *self);

// Handle lights
void runLights(Program *self);
void setLight(Program *self, int dir);

#endif /* PROGRAM_H_ */
