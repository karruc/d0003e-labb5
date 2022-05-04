#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "GUI.h"

void writeChar(char ch, int pos) {
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

void printCurrentChar(GUI *self){
	if (self->currentFrequency == 0){
		LCDDR1 = (1 << 0);
	} else if (self->currentFrequency == 1){
		LCDDR1 = (1 << 4);
	}
}

void switchFrequency(GUI * self, int val){
    self->currentFrequency = val;
    printCurrentChar(self);
}

void newDisplayFrequency(GUI *self, int frequency){
    //Save current frequency in temp var for comparisions
    int temp = self->currentFrequency;

    int pos = 2; //Frequency is printed at position depending on id
    if(temp == 0){
        pos = 0;
    } else if (temp == 1){
        pos = 4;
    }

    printAt(pos, frequency);
}

void printAt(int pos, int val){
	writeChar((val%100)/ 10 + '0', pos);
	pos++;
	writeChar(val%10 + '0', pos);
}

void LCD_init(void){

    CLKPR = 0x80;
	CLKPR = 0x00;

    LCDCRA = (1 << LCDEN) | (1 << LCDAB);	
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	LCDDR1 = (1 << 0);

    //Write 0 on display to notify user writing working properly
	 writeChar('0', 0);
	 writeChar('0', 1);
	 writeChar('0', 4);
	 writeChar('0', 5);
     
	//TCCR1B = (1 << CS12) | (1 << CS10) | (1 << WGM12);
}

void IO_init(void){
    //init
 	 EIMSK = (1<<PCIE1) | (1<<PCIE0) | EIMSK;
	 
	 //btn down
	 PORTB = (1<<PB7) | PORTB;
	 PCMSK1 = (1<<PCINT15) | PCMSK1;
	 
	 //btn up
	 PORTB = (1<<PB6) | PORTB;
	 PCMSK1 = (1<<PCINT14) | PCMSK1;
	 
	 //btn right
	 PORTE = (1<<PE3) | PORTE;
	 PCMSK0 = (1<<PCINT3) | PCMSK0;
	 
	 //btn left
	 PORTE = (1<<PE2) | PORTE;
	 PCMSK0 = (1<<PCINT2) | PCMSK0;
	 
	 //btn center
	 PORTB = (1<<PB4) | PORTB;
	 PCMSK1 = (1<<PCINT12) | PCMSK1;
}

void initIO(){
    //PORTE output pin 1 and 3
    DDRE = (1<<DDE1) | (1<<DDE3);

    LCD_init();
    IO_init();
}