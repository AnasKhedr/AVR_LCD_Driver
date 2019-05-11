/*
 * LCD_Lib.cpp
 *
 * Created: 29-Mar-19 11:52:55 PM
 * Author : Anas Khedr
 */
#define F_CPU 8000000UL

#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>			//for _delay_ms()
#include <string.h>				//for strlen()
#include <stdarg.h>				//for va_list
#include <stdio.h>				//for vsprintf()

#define BUFFER_SIZE 40			//each LCD display has 80 location. if it's a 2-Line LCD then 40 per-line (only 16 characters are visible per-line in 16x2 LCD)
char buffer[BUFFER_SIZE];

MyLCD::MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t RS,uint8_t E){
	_delay_ms(11);
	switch (Port_of_D)
	{
		case 'B':
			DDRB |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(RS) | _BV(E);
			//PORTB _SFR_IO8(0x05)
			//PINB _SFR_IO8(0x03)
			Port_of_D=0x05;
			break;
		case 'C':
			DDRC |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(RS) | _BV(E);
			//PORTC _SFR_IO8(0x08)
			//PINC _SFR_IO8(0x06)
			Port_of_D=0x08;
			break;
		case 'D':
			DDRD |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(RS) | _BV(E);
			//PORTD _SFR_IO8(0x0B)
			//PIND _SFR_IO8(0x09)
			Port_of_D=0x0B;
			break;
	}
	
	pins.Port_of_D=Port_of_D;
	pins.D7=D7;
	pins.D6=D6;
	pins.D5=D5;
	pins.D4=D4;
	pins.RS=RS;
	pins.E=E;
	
	pins.RW_Status=0;		//0 => NOT using(issuing) read/write(RW) command/pin (only write by default)
	pins.wire_num=0;		//0 => 4-wires & 1 => 8-wires
	
}

MyLCD::MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t RS,uint8_t RW,uint8_t E) : MyLCD(Port_of_D,D7,D6,D5,D4,RS,E){
	
	_SFR_IO8(pins.Port_of_D) |= _BV(RW);
	pins.RW=RW;
	pins.RW_Status=1;		//1 => using(issuing) read/write(RW) command/pin
	pins.wire_num=0;		//0 => 4-wires & 1 => 8-wires
}

MyLCD::MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t E){
//:MyLCD( Port_of_D, D7, D6, D5, D4, RS, E){
	_delay_ms(11);
	//if(Port_of_D == Port_of_registers) return -1; //error in Atmel328p but may work in other MCU
	switch (Port_of_D)
	{
		case 'B':
		DDRB |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(D3) | _BV(D2) | _BV(D1) | _BV(D0);
		//PORTB _SFR_IO8(0x05)
		//PINB _SFR_IO8(0x03)
		Port_of_D=0x05;
		break;
		case 'C':
		DDRC |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(D3) | _BV(D2) | _BV(D1) | _BV(D0);
		//PORTC _SFR_IO8(0x08)
		//PINC _SFR_IO8(0x06)
		Port_of_D=0x08;
		break;
		case 'D':
		DDRD |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(D3) | _BV(D2) | _BV(D1) | _BV(D0);
		//PORTD _SFR_IO8(0x0B)
		//PIND _SFR_IO8(0x09)
		Port_of_D=0x0B;
		break;
	}
	//-------------------------------
	
	switch (Port_of_registers)
		{
			case 'B':
				DDRB |= _BV(RS) | _BV(E);
				//PORTB _SFR_IO8(0x05)
				Port_of_registers=0x05;
				break;
			case 'C':
				DDRC |= _BV(RS) | _BV(E);
				//PORTC _SFR_IO8(0x08)
				Port_of_registers=0x08;
				break;
			case 'D':
				DDRD |= _BV(RS) | _BV(E);
				//PORTD _SFR_IO8(0x0B)
				Port_of_registers=0x0B;
				break;
		}
	
	pins.Port_of_D=Port_of_D;
	pins.D7=D7;
	pins.D6=D6;
	pins.D5=D5;
	pins.D4=D4;
	pins.D3=D3;
	pins.D2=D2;
	pins.D1=D1;
	pins.D0=D0;
	
	pins.Port_of_registers=Port_of_registers;
	pins.RS=RS;
	pins.E=E;
	
	pins.RW_Status=0;			//0 => NOT using(issuing) read/write(RW) command/pin (only write by default)
	pins.wire_num=1;			//1 => 8-wires & 0 => 4-wires
	
}

MyLCD::MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t RW,uint8_t E) \
:MyLCD(Port_of_D, D7, D6, D5, D4, D3, D2, D1, D0, Port_of_registers, RS, E){
	
	_SFR_IO8(pins.Port_of_D) = _BV(RW);
	pins.RW=RW;
	pins.RW_Status=1;			//1 => using(issuing) read/write(RW) command/pin
	pins.wire_num=1;			//1 => 8-wires & 0 => 4-wires
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void MyLCD::send(){											//send command/data to LCD
	if(pins.wire_num){										//1 => 8-wires & 0 => 4-wires
		_SFR_IO8(pins.Port_of_registers) |= _BV(pins.E);	//E High
		_delay_us(1000);
		_SFR_IO8(pins.Port_of_registers) &=~ _BV(pins.E);	//then E low
		_delay_us(1000);
	}else{													//0 => 4-wires & 1 => 4-wires
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.E);			//E High
		_delay_us(1000);
		_SFR_IO8(pins.Port_of_D) &=~ _BV(pins.E);			//then E low
		_delay_us(1000);
	}
	
	
	if(pins.wire_num){									//1 => 8-wires & 0 => 4-wires
		_SFR_IO8(pins.Port_of_D) = 0x00;				//reset all pins D0-D7 for next use of |=
	}
	else{
		_SFR_IO8(pins.Port_of_D) &=~ ((1<<pins.D7) | (1<<pins.D6) | (1<<pins.D5) | (1<<pins.D4)); //reset used pins D4-D7 for next use of |=
	}
}

void MyLCD::command(){
	if(pins.wire_num){					//1 => 8-wires
		_SFR_IO8(pins.Port_of_registers) &=~ _BV(pins.RS);
	}
	else{								//0 => 4-wires
		_SFR_IO8(pins.Port_of_D) &=~ _BV(pins.RS);
	}
}

void MyLCD::data(){
	if(pins.wire_num){					//1 => 8-wires
		_SFR_IO8(pins.Port_of_registers) |= _BV(pins.RS);
	}
	else{								//0 => 4-wires
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.RS);
	}
}

void MyLCD::clear(){
	command();
	writeChar(0x1);
	_delay_us(1.64);
}

void MyLCD::home(){
	command();
	writeChar(0x2);
	_delay_ms(1.64);
}

bool MyLCD::read(){
	if (pins.wire_num){		//pins.wire_num == 1 => 8-wires
		if (pins.RW_Status){	//1 => using(issuing) read/write(RW) command/pin
			_SFR_IO8(pins.Port_of_registers) |= _BV(pins.RW);	//set RW pin to 1 to read
			//the user should select what is he\she is reading data\command and its address
			
			send();												//send command to LCD
			
			pins.buffer = _SFR_IO8(pins.Port_of_D-2);			//read from PINx where x is the port you selected and store value in buffer
			return 0;
		}
		else{					//0 => NOT using(issuing) read/write(RW) command/pin
			//error pins.RW_Status cant be 0, that means you only write
			return 1;
		}
	}
	return 0;
}

void MyLCD::writeChar(char buffer){	//write data on D7-D4 or D7-D0 (according to 4\8-wire mode) without using E(enable pin) "without invoking send();"
	pins.buffer=buffer;
	if (pins.wire_num){			//pins.wire_num == 1 => 8-wires
		if (pins.RW_Status){	//1 => using(issuing) read/write(RW) command/pin
			
			_SFR_IO8(pins.Port_of_registers) &=~ _BV(pins.RW);	//reset RW pin to 0 to write
			//the user should select what is he\she is reading data\command and its address
			//fullWrite();
			//send();
		}
		else{					//0 => NOT using(issuing) read/write(RW) command/pin
			//the user should select what is he\she is reading data\command and its address
		}
		fullWrite();
		send();
		/*
		_SFR_IO8(pins.Port_of_D) = pins.buffer;					//output the command\data on the pins of D7-D0
		_SFR_IO8(pins.Port_of_registers) |= _BV(pins.E);		//E high
		_delay_us(1000);
		_SFR_IO8(pins.Port_of_registers) &=~ _BV(pins.E);		//the E low
		*/
	}else{														//pins.wire_num == 0 => 4-wires
		if(pins.RW_Status){										//1 => using(issuing) read/write(RW) command/pin
			_SFR_IO8(pins.Port_of_registers) &=~ _BV(pins.RW);	//reset RW pin to 0 to write
		}
		else{													//0 => NOT using(issuing) read/write(RW) command/pin
				//no need to reset RW since you're not using RW
			}
			upperWrite();
			send();
			lowerWrite();
			send();
		}
		
	//_SFR_IO8(pins.Port_of_D) = 0x00;		//reset the PORT cuz |= will keep the pin 1		"send() clears it insted"
}

void MyLCD::upperWrite(){
	if(pins.buffer & _BV(7))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D7);
	if(pins.buffer & _BV(6))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D6);
	if(pins.buffer & _BV(5))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D5);
	if(pins.buffer & _BV(4))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D4);

}

void MyLCD::lowerWrite(){
	if(pins.wire_num){								//pins.wire_num == 1 => 8-wires
		if(pins.buffer & _BV(3))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D3);
		if(pins.buffer & _BV(2))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D2);
		if(pins.buffer & _BV(1))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D1);
		if(pins.buffer & _BV(0))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D0);
	}
	else{											//pins.wire_num == 0 => 4-wires
		pins.buffer = pins.buffer <<4;
		upperWrite();
	}
	
}

void MyLCD::fullWrite(){
	upperWrite();
	lowerWrite();
}

void MyLCD::printString(char* str){
	uint8_t i;
	data();
	for(i=0;i<strlen(str);i++){
		writeChar(str[i]);
	}
}

void MyLCD::print(const char* format, ...){
	va_list arguments;
	va_start(arguments,format);
	
	vsprintf(buffer,format,arguments);
	va_end(arguments);
	
	printString(buffer);
}

void MyLCD::print(char* str){
	printString(str);
}

void MyLCD::print(char ch){
	data();
	writeChar(ch);
}
/*
void MyLCD::init(uint8_t Lines){
	Lines--;
	char fun_set = 0b00110000;  //this is the default command "function set"
	fun_set |= Lines<<3 | pins.wire_num<<4;
	_SFR_IO8(pins.Port_of_D) = fun_set;
	send();
	clear();
}
*/
void MyLCD::init(uint8_t Lines,bool Cursor,bool Blink,bool Resolution){	//C is Cursor underline on\off and B is Blink on\off
	Lines--;
	char fun_set = 0b00100000;  //this is the default command "function set"
	char display = 0b00001100;  //this is the default command "Display on\off & cursor" with display set on
	fun_set |= Lines<<pins.D3 | pins.wire_num<<pins.D4 | Resolution<<pins.D2;
	display |= Cursor<<1 | Blink<<0;
	command();
	if(!pins.wire_num){			//pins.wire_num == 0 => 4-wires
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D5);	//this is the function set command for choosing 4-bit mode
		send();
	}
	writeChar(fun_set);
	_delay_ms(4.1);
	writeChar(display);
	_delay_ms(4.1);
	clear();
	_delay_ms(4.1);
	//writeDirecion(0,0,0);		//this is set by default
	//send();
}


void MyLCD::setCursor(bool Line,uint8_t address){
	address += Line*(0x40);			//0x40 is the start address of Line 2
	command();
	writeChar(address|0x80);		//0x80 which is 0b10000000 to tell the LCD that this is display address
	
}

void MyLCD::shift(uint8_t direction, uint8_t num, short delay){
	if(direction){
		direction = 0x18;						//0x18 which is 0b00011000 to tell the LCD to shift the addresses left one time
	}
	else if(direction==0){
		direction = 0x1C;						//0x1C which is 0b00011100 to tell the LCD to shift the addresses right one time
	}

	uint8_t i;
	command();
	
	for(i=0;i<num;i++){
		writeChar(direction);					//write the binary for Right or Left (whatever user chose) to D7-D4,0
		for(short i=1;i<delay;i+=10){
			_delay_ms(10);
		}
	}
}

void MyLCD::shiftL(uint8_t num, short delay){
	shift(LEFT,num,delay);
}

void MyLCD::shiftR(uint8_t num, short delay){
	shift(RIGHT,num,delay);
}

void MyLCD::displayShift(char fixedStartAddress, bool line, bool direction){
	setCursor(line,fixedStartAddress);
	command();
	if(direction){
		writeChar(0b00000111);
	}
	else{
		writeChar(0b00000110);
	}
}

void MyLCD::writeDirection(char startAddress/* =0x00 */, bool Line/* =0 */, bool direction/* =LtoR */){
	setCursor(Line,startAddress);
	command();
	if(direction){
		writeChar(0b0110);
	}
	else{
		writeChar(0b0100);
		/* This sites the visible part of the display to be the left part(from 0x18 to 0x27)
		if(startAddress == ENDADDRESS)
			shiftR(0x18,0);
		*/
	}
}


uint8_t MyLCD::defineGraph(char graph[8], uint8_t address/* =0 */){
	static uint8_t idx=0x40;		//this is the first address we can save a new char in
	if(address){
		idx = 0x40 | address*8;
	}
	
	if(idx >= 0x80){				//you have defined 8 new characters which is the max number on new characters that can be defined
		//return -1;				//return error (0xff)
	}
	
	command();
	writeChar(idx);
	
	data();
	for(uint8_t i=0; i<8;i++){
		writeChar(graph[i]);
	}
	
	idx+=8;
	return (idx-0x40)/8 -1;				//return the address which you can use to print the char you defined
}