/*
 * inputHandler.h
 *
 * Created: 2022-05-04 11:06:42
 *  Author: 
 */ 


#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include Controller.h
#include GUI.h
#include TinyTimber.h
#include <avr/io.h>

#define nCar (1<<0)
#define sCar (1<<2)

#define nBridge (1<<1)
#define sBridge (1<<3)


typedef struct {
    Object super;
    GUI *gui;
    Controller *controller;
} IH;

#define initIH(gui, controller) {initObject(), gui, controller}

void input(IH *self);

#endif /* INPUTHANDLER_H_ */