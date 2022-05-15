/*
 * controller.c
 *
 * Created: 2022-05-04 11:07:46
 *  Author: 
 */ 

#include "controller.h"

void newCarInQueue(Controller *self, int dir){
    if(dir == N){
        //Increment North queue
        self->queue[N]++;
        //Update GUI
        ASYNC(self->gui, printQueueTowardsNorth, self->queue[N]);
    } else if(dir == S){
        //Increment South queue
        self->queue[S]++;
        //Update GUI
        ASYNC(self->gui, printQueueTowardsSouth, self->queue[S]);
    }
}

void deleteCarFromQueue(Controller *self, int dir){
    if(dir == N){
        //Decrease North queue
        self->queue[N]--;
        //Update GUI
        ASYNC(self->gui, printQueueTowardsNorth, self->queue[N]);
    } else if(dir == S){
        //Decrease South queue
        self->queue[S]--;
        //Update GUI
        ASYNC(self->gui, printQueueTowardsSouth, self->queue[S]);
    }
}

void newCarOnBridge(Controller *self, int dir){
    deleteCarFromQueue(self, dir);
    self->brDir = dir;
    self->passed++;
    self->queue[B]++;
    ASYNC(self->gui, printCarsOnBridge, self->queue[B]);
    AFTER(MSEC(5000), self, deleteCarFromBridge, NULL);
}

void deleteCarFromBridge(Controller *self){
    self->queue[B]--;
    ASYNC(self->gui, printCarsOnBridge, self->queue[B]);
}

void redLight(Controller *self){
    self->passed = 0;
    self->lights = BOTHRED;
    ASYNC(self->OpH, lightsOut, self->lights);
}

void greenLight(Controller *self, int dir){
    self->lights = dir;
    ASYNC(self->OpH, lightsOut, self->lights);
}

void nLights(Controller *self){
    //If there are cars in the north queue we also check if
    //not enough cars have passed or there are no cars waiting in south
    if(self->queue[N] > 0 && (self->passed <= maxTrough || self->queue[S] ==0)){
        //Let north cars pass
        greenLight(self, N);
        AFTER(MSEC(1000), self, nLights, NULL);
    } else if(self->queue[B] != 0 && self->queue[S] != 0 && self->brDir == N){
        redLight(self);
        AFTER(MSEC(5000), self, sLights, NULL);
    } else {
        redLight(self);
        AFTER(MSEC(1000), self, sLights, NULL);
    }
}

void sLights(Controller *self){
    if(self->queue[S] > 0 && (self->passed <= maxTrough || self->queue[N] ==0)){
        //Let north cars pass
        greenLight(self, S);
        AFTER(MSEC(1000), self, sLights, NULL);
    } else if(self->queue[B] != 0 && self->queue[S] != 0 && self->brDir == N){
        redLight(self);
        AFTER(MSEC(5000), self, nLights, NULL);
    } else {
        redLight(self);
        AFTER(MSEC(1000), self, nLights, NULL);
    }  
}

void startController(Controller *self){
    //Update GUI to display current queues at init
    ASYNC(self->gui, startGUI, NULL); 
	ASYNC(self->gui, printQueueTowardsNorth, self->queue[N]); 
	ASYNC(self->gui, printQueueTowardsSouth, self->queue[S]);
	ASYNC(self->gui, printCarsOnBridge, self->queue[B]);
	
	//Set initial light to north
	ASYNC(self, nLights, NULL);
}