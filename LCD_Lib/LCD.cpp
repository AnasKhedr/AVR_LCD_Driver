/*
 * LCD_Lib.cpp
 *
 * Created: 29-Mar-19 11:52:55 PM
 * Author : Anas Khedr
 */ 

//#define F_CPU 1000000UL

#include "LCD.h"
#include <avr/io.h>
#include <util/delay.h>


MyLCD::MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t RS,uint8_t E){
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
	
	pins.RW=RW;
	pins.RW_Status=1;		//1 => using(issuing) read/write(RW) command/pin
	pins.wire_num=0;		//0 => 4-wires & 1 => 8-wires
}

MyLCD::MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t E) \
:MyLCD( Port_of_D, D7, D6, D5, D4, RS, E){
	
	//if(Port_of_D == Port_of_registers) return -1; //error in Atmel328p but may work in other MCU
	switch (Port_of_registers)
		{
			case 'B':
				DDRB |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(RS) | _BV(E);
				//PORTB _SFR_IO8(0x05)
				Port_of_registers=0x05;
				break;
			case 'C':
				DDRC |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(RS) | _BV(E);
				//PORTC _SFR_IO8(0x08)
				Port_of_registers=0x08;
				break;
			case 'D':
				DDRD |= _BV(D7) | _BV(D6) | _BV(D5) | _BV(D4) | _BV(RS) | _BV(E);
				//PORTD _SFR_IO8(0x0B)
				Port_of_registers=0x0B;
				break;
		}
	
	pins.D3=D3;
	pins.D2=D2;
	pins.D1=D1;
	pins.D0=D0;
	pins.Port_of_registers=Port_of_registers;
	
	pins.RW_Status=0;			//0 => NOT using(issuing) read/write(RW) command/pin (only write by default)
	pins.wire_num=1;			//1 => 8-wires & 0 => 4-wires
}

MyLCD::MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t RW,uint8_t E) \
:MyLCD(Port_of_D, D7, D6, D5, D4, D3, D2, D1, D0, Port_of_registers, RS, E){
	
	pins.RW=RW;
	pins.RW_Status=1;			//1 => using(issuing) read/write(RW) command/pin
	pins.wire_num=1;			//1 => 8-wires & 0 => 4-wires
}

//----------------------------------------------------------------------------------------------------------------------------------------------

void MyLCD::send(){										//send command/data to LCD
	_SFR_IO8(pins.Port_of_registers) |= _BV(pins.E);	//E High
	_delay_us(1000);
	_SFR_IO8(pins.Port_of_registers) &=~ _BV(pins.E);	//then E low
	_delay_us(1000);
	if(pins.wire_num){									//1 => 8-wires & 0 => 4-wires
		_SFR_IO8(pins.Port_of_D) = 0x00;				//reset all pins D0-D7 for next use of |=
	}
	else{
		_SFR_IO8(pins.Port_of_D) &=~ ((1<<pins.D7) | (1<<pins.D6) | (1<<pins.D5) | (1<<pins.D4));
	}
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

void MyLCD::write(char buffer){
	pins.buffer=buffer;
	if (pins.wire_num){			//pins.wire_num == 1 => 8-wires
		if (pins.RW_Status){	//1 => using(issuing) read/write(RW) command/pin
			
			_SFR_IO8(pins.Port_of_registers) &=~ _BV(pins.RW);	//reset RW pin to 0 to write
			//the user should select what is he\she is reading data\command and its address
			fullWrite();
			send();
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
				
			}
			upperWrite();
			send();
			lowerWrite();
			send();
		}
		
	
	_SFR_IO8(pins.Port_of_D) = 0x00;		//reset the PORT cuz |= will keep the pin 1
}

void MyLCD::upperWrite(){
	if(pins.buffer<<7 & _BV(pins.D7))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D7);
	if(pins.buffer<<6 & _BV(pins.D6))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D6);
	if(pins.buffer<<5 & _BV(pins.D5))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D5);
	if(pins.buffer<<4 & _BV(pins.D4))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D4);

}

void MyLCD::lowerWrite(){
	if(pins.wire_num){								//pins.wire_num == 1 => 8-wires
		if(pins.buffer<<3 & _BV(pins.D3))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D3);
		if(pins.buffer<<2 & _BV(pins.D2))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D2);
		if(pins.buffer<<1 & _BV(pins.D1))
		_SFR_IO8(pins.Port_of_D) |= _BV(pins.D1);
		if(pins.buffer<<0 & _BV(pins.D0))
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

void MyLCD::command(){
	if(!pins.wire_num){
		_SFR_IO8(pins.Port_of_D) = 1<<pins.RS;
		_SFR_IO8(pins.Port_of_D) = 1<<pins.RW;
	}
}


void MyLCD::init(uint8_t Lines){
	Lines--;
	char fun_set = 0b00110000;  //this is the default command "function set"
	fun_set |= Lines<<3 | pins.wire_num<<4;
	_SFR_IO8(pins.Port_of_D) = fun_set;
}

void MyLCD::init(uint8_t Lines,uint8_t C,uint8_t B){
	Lines--;
	char fun_set = 0b00110000;  //this is the default command "function set"
	char display = 0b00001000;  //this is the default command "Display on\off & cursor"
	fun_set |= Lines<<3 | pins.wire_num<<4;
}
