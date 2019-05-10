/*
 * LCD.h
 *
 * Created: 29-Mar-19 11:54:22 PM
 *  Author: Anas Khedr
 */ 
#define F_CPU 8000000UL

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>			//for _delay_ms()
#include <string.h>				//for strlen()
#include <stdarg.h>				//for va_list
#include <stdio.h>				//for vsprintf()

#define WRITEONLY 1
#define ENDADDRESS 0x27

#define RIGHT 1			//direction of shift to use with MyLCD::shift()
#define LEFT 0

#define LtoR 1
#define RtoL 0
#define LtoR 1

#define CURSOR_UNDERLINE_ON  1
#define CURSOR_UNDERLINE_OFF 0
#define BLINK_ON 1
#define BLINK_OFF 0
#define RESOLUTION_5x10 1
#define RESOLUTION_5x7  0

typedef unsigned char uint8_t;


class MyLCD
{
public:
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t RW,uint8_t E);
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t E);
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t RS,uint8_t RW,uint8_t E);
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t RS,uint8_t E);
	
	void command();							//call this function before using writeChar() to send a command
	void data();							//call this function before using writeChar() to send a data(a character)
	
	void clear();							//clear the LCD (basically reset it)
	void home();							//return the cursor and the display to initial position without reseting everything (command: display and cursor home)
	
	//bool read();
	void writeChar(char buffer);			//Helper Function, you need to specify what you are sending it (Data or Command)
	
	void upperWrite();						//Helper to Helper
	void lowerWrite();						//Helper to Helper
	void fullWrite();						//Helper to Helper
	
	void printString(char* str);			//Main(accepts string array only) and Helper
	void print(const char* format, ...);	//Main(works like printf for the display)
	void print(char* str);
	void print(char ch);
	
	void send();
	
	void init(uint8_t Lines=2,bool Cursor=CURSOR_UNDERLINE_ON,bool Blink=BLINK_OFF,bool Resolution=RESOLUTION_5x7);
	//void init(uint8_t Lines);
	
	void setCursor(bool Line,uint8_t address);
	void shiftR(uint8_t num, short delay=100);						//shift the visible part of the display(not the cursor) to the right
	void shiftL(uint8_t num, short delay=100);						//shift the visible part of the display(not the cursor) to the left
	void shift(uint8_t direction, uint8_t num, short delay=100);
	
	void displayShift(char fixedStartAddress=0x10, bool line=0, bool direction=LtoR);
	void writeDirection(char startAddress=0x00, bool Line=0, bool direction=LtoR);
	
	uint8_t defineGraph(char graph[8], uint8_t address=0);			
	//use this site to generate your custom character :https://www.quinapalus.com/hd44780udg.html
private:
	struct storage{
		uint8_t RS:3,RW:3,E:3,D0:3,D1:3,D2:3,D3:3,D4:3,D5:3,D6:3,D7:3,Port_of_D:4,Port_of_registers:4,wire_num:1,RW_Status:1;
		uint8_t buffer;
	}pins;
};




#endif /* LCD_H_ */