/*
 * outputHandler.h
 *
 * Created: 2022-05-04 11:06:59
 *  Author: 
 */ 


#ifndef OUTPUTHANDLER_H_
#define OUTPUTHANDLER_H_

#include "TinyTimber.h"
#include <avr/io.h>
#include <stdint.h>

typedef struct {
	Object super;
} OH;

#define initOH(){initObject()}

void lightsOut(OH *self, int lightsOn);

#endif /* OUTPUTHANDLER_H_ */