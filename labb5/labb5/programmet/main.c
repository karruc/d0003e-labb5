/*
 * labb5.c
 *
 * Created: 2022-05-04 11:04:48
 * Author : 
 */ 

#include <avr/io.h>

#include "controller.h"
#include "GUI.h"
#include "inputHandler.h"
#include "outputHandler.h"
#include "TinyTimber.h"


int main(void)
{
	GUI gui = initGUI();
	OH oh = initOH();
	Controller controller = initController(&oh, &gui);
	IH ih = IH(&controller, &gui);
	
	INSTALL (&ih, &input, IRQ_USART0_RX);
	
	return TINYTIMBER(&controller, initialize, NULL);

}

