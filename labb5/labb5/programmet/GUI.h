/*
 * GUI.h
 *
 * Created: 2022-05-04 11:06:02
 *  Author: 
 */ 

#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"

#include <setjmp.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

typedef struct {
	Object super;
} GUI;

#define initGUI(){initObject()}

void LCD_init(void);
void USART_init(void);
void init(GUI *self);
void writeChar(char ch, int pos);
void printAt(int pos, int val);
void printQueueTowardsNorth(GUI *self, int queueLength);
void printQueueTowardsSouth(GUI *self, int queueLength);
void printCarsOnBridge(GUI *self, int carsOnBridge);

#endif /* GUI_H_ */