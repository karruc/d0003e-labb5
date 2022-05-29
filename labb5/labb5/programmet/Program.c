
#include "CommonLibraries.h"
#include "Program.h"
#include "TinyTimber.h"
#include "SignalInterface.h"
#include "UserInterface.h"

void startProgram(Program *self) {
	
	//Update GUI to display current queues at init
	ASYNC(self->ui, initUI, NULL);
	ASYNC(self->ui, updateOutput, self->carQueues);
	
	// Start running the lights.
	setLight(self, BOTHRED);
	
	setLight(self, GREENTONORTH);
	
	setLight(self, GREENTOSOUTH);
	
	ASYNC(self, runLights, NULL);
}

void addCarQueue(Program *self, int dir) {
	if (dir == N) {
		self->carQueues[N]++;
	} else if (dir == S) {
		self->carQueues[S]++;
	}
	ASYNC(self->ui, updateOutput, self->carQueues);
}

void addCarBridge(Program *self, int dir) {
	if(dir == N){
		self->carQueues[N]--;
		} else if(dir == S) {
		self->carQueues[S]--;
	}
	
	self->carsSinceLightSwitch++;
	self->carQueues[B]++;
	
	ASYNC(self->ui, updateOutput, self->carQueues);
	AFTER(SEC(5), self, deleteCarBridge, NULL);
}

void deleteCarBridge(Program *self) {
	self->carQueues[B]--;
	ASYNC(self->ui, updateOutput, self->carQueues);
}

void runLights(Program *self) {
	
	
	// Handle situation where both lights are red. If any cars are still on the bridge
	// these has to be taken into consideration.
	if (self->lightDirection == BOTHRED) {
		
		// If the bridge is empty, bridge status can be reset, and be fully ready to 
		// turn green for any arriving cars.
		if (self->carQueues[B] == 0) {
			
			self->travelDirection = BOTHRED;		
			self->carsSinceLightSwitch = 0;
			
			if (self->carQueues[N] > 0) {
				self->travelDirection = N;
				setLight(self, GREENTONORTH);
			} else if (self->carQueues[S] > 0) {
				self->travelDirection = S;
				setLight(self, GREENTOSOUTH);
			}
		}
		
		// Bridge is occupied, if anyone has arrived in the current travel direction
		// without the max pass being reached they should be allowed to enter the bridge.
		else if (self->travelDirection != BOTHRED &&
				self->carsSinceLightSwitch < maxTrough &&
				self->carQueues[self->travelDirection] > 0) {
			setLight(self, self->travelDirection);
		}
	} 
	
	// Handle situation where one direction has a green light, keep the light green 
	// until the queue is empty or the max pass limit is reached.
	else if (self->lightDirection != BOTHRED) {
		
		// If no cars are left in the given direction.
		if (self->carQueues[self->lightDirection] == 0 ||
			self->carsSinceLightSwitch >= maxTrough) {
			setLight(self, BOTHRED);
		} else {
			setLight(self, self->lightDirection);
		}
	}
	
	// Rerun update loop every 200ms.
	AFTER(SEC(1), self, runLights, NULL);
}

void setLight(Program *self, int dir) {
	//self->carQueues[N] += 10;
	//ASYNC(self->ui, updateOutput, self->carQueues);
	self->lightDirection = dir;
	ASYNC(self->si, sendLightSignal, self->lightDirection);
}
