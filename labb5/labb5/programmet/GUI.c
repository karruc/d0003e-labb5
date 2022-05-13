/*
 * GUI.c
 *
 * Created: 2022-05-04 11:05:44
 *  Author: 
 */ 

#include "GUI.h"

void LCD_init(void){

	CLKPR = 0x80;
	CLKPR = 0x00;

	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	LCDDR1 = (1 << 0); // LCDDR8 = 0x1;
}

void USART_init(void){
	#define AsyncNormalUBRREquation (8000000/16/9600-1)
	
	UCSR0B = (1 << RXEN0 ) | (1 << TXEN0)| (1 << RXCIE0) ;
	UCSR0C = (1 << UCSZ01 )| (1 << UCSZ00);
	UBRR0H = (unsigned char)(AsyncNormalUBRREquation >> 8);
	UBRR0L = (unsigned char)AsyncNormalUBRREquation;
}

void init(GUI *self){
	LCD_init();
	USART_init();
}

void writeChar(char ch, int pos){
	uint16_t SCC;

	const uint16_t LCD_SegTable[10] = {
		0x1551,     // '0'
		0x0110,     // '1'
		0x1E11,     // '2
		0x1B11,     // '3
		0x0B50,     // '4
		0x1B41,     // '5
		0x1F41,     // '6
		0x4009,     // '7
		0x1F51,     // '8
		0x1B51      // '9'

	};
	if (ch <= '9' && ch >= '0'){
		SCC = LCD_SegTable[ch-'0'];
		} else {
		SCC = 0x0000;
	}
	
	uint8_t *LCDDRx;
	LCDDRx = (uint8_t*) 0xEC;			// Memory adrress to LCDDR0
	uint16_t tmp_data = 0x0; //For nibble bits 3:0
	uint8_t mask;
	
	LCDDRx += pos >> 1;

	mask = ((pos%2 == 0) ? 0xF0 : 0x0F);

	for(int i = 0; i < 4; i++){
		tmp_data = SCC & 0xF;
		SCC = SCC >> 4;
		
		if(pos % 2 != 0){
			tmp_data = tmp_data << 4;
		}
		
		*LCDDRx = tmp_data | (mask & *LCDDRx);
		LCDDRx += 5;
	}

	return;
}

void printAt(int pos, int val){
	writeChar((val%100)/ 10 + '0', pos);
	pos++;
	writeChar(val%10 + '0', pos);
}

// The length of the queue of cars waiting to enter the bridge in northbound direction
void printQueueTowardsNorth(GUI *self, int queueLength){
	printAt(0, queueLength); // kanske printAt(1, queueLength);
}

// The length of the queue of cars waiting to enter the bridge in southbound direction
void printQueueTowardsSouth(GUI *self, int queueLength){
	printAt(2, queueLength); // kanske printAt(3, queueLength);
}

// The number of cars currently on the bridge
void printCarsOnBridge(GUI *self, int carsOnBridge){
	printAt(4, carsOnBridge); // kanske printAt(5, queueLength);
}