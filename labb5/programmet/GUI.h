
#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"

typedef struct{
    Object super;
    int currentFrequency;
}GUI;

#define initGUI() {initObject(), 0}

void setup(void);
void switchFrequency(GUI *self, int val);
void writeCurrent(GUI *self);
void printCurrentChar(GUI *self);
void newDisplayFrequency(GUI *self, int frequency);
void initIO(void);

#endif