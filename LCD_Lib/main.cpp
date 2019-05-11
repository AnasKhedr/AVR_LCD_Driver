/*
 * GccApplication1.cpp
 *
 * Created: 02-Apr-19 11:38:15 PM
 * Author : anas
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include "LCD.h"
#include <util/delay.h>
#include "string.h"
#include <stdio.h>

int main(void){
	//check the header file to see all available constructors and how to use 8-bit mode if you want
	MyLCD lcd('D',7,6,5,4,3,2);					//set the pins that connect the lcd to the MCU: (connected to port D, D7 of the LCD is connected to pin 7 or PORT D, D6 of the LCD is connected to pin 6 or PORT D, D5 of the LCD is connected to pin 5 or PORT D, D4 of the LCD is connected to RS or PORT D, D7 of the LCD is connected to pin 3 or PORT D, E of the LCD is connected to pin 2 or PORT D)
	lcd.init(2,1,0);							//set up the LCD, the LCD has 2 lines, show the cursor underline , don't blink (those are the same as the default arguments so if you just called init(); it would have had the same parameter, hence same effect)

	char customChar0[] = {0,14,21,23,17,14,0,0};//clock
	char customChar1[] = {10,10,31,31,14,4,4,0};//fesha
	char customChar2[] = {4,4,31,0,14,4,4,0};	//capacitor
	char customChar3[] = {0,10,10,0,17,14,0,0};	//smiley face
	
	//define new graphs or characters (use this site to create the string array needed: https://www.quinapalus.com/hd44780udg.html
	uint8_t clock_handler=lcd.defineGraph(customChar0);	//clock
	uint8_t fesha_handler=lcd.defineGraph(customChar1);	//fesha
	uint8_t cap_handler  =lcd.defineGraph(customChar2);	//capacitor
	uint8_t Sface_handler=lcd.defineGraph(customChar3);	//smiley face
	
	lcd.clear();		//clear the display since defineGraph() misses with display
	lcd.home();			//rest display position and remove any shifts
	lcd.setCursor(0,0);	//this is useless since home() restes diplay posithion
	
	lcd.data();								//must tell the LCD that you'll be sending data() if you want to use writeChar() [writeChar() could be used to send command() as well]
	lcd.writeChar(Sface_handler);			//send a char to the lcd (whether this char is a command() or data() is set by thes two APIs)
	lcd.print(" Hello ");					//print a char* (this is an overloaded function that can handle char, char* and vlist)
	lcd.print(Sface_handler);				//print a char  (this is an overloaded function that can handle char, char* and vlist)
	lcd.setCursor(1,0);						//go to the first pixel of line 1 (second line)
	lcd.print("defined chars: %c %c %c %c",clock_handler,Sface_handler,fesha_handler,cap_handler);//print a vlist very much the same as printf (this is an overloaded function that can handle char, char* and vlist)
	_delay_ms(300);

    while (1) 
    {
		lcd.shiftR(6,100);					//shift the visible part of the LCD 6 times to the Right with a 100ms delay between each single shift
		_delay_ms(200);
		lcd.shiftL(6,100);					//shift the visible part of the LCD 6 times to the Right with a 100ms delay between each single shift
		_delay_ms(200);
		
		/*
		lcd.print("size of struct:%d",sizeof(tempx));
		_delay_ms(3000);
		lcd.clear();
		
		lcd.print("size of char:%d",sizeof(char));
		_delay_ms(3000);
		lcd.clear();
		
		lcd.print("size of int:%d",sizeof(int));
		_delay_ms(3000);
		lcd.clear();
		
		lcd.print("size of short:%d",sizeof(short));
		_delay_ms(3000);
		lcd.clear();
		
		lcd.print("size of float:%d",sizeof(float));
		_delay_ms(3000);
		lcd.clear();
		*/
		/*
		_delay_ms(1000);
		x++;
		lcd.setCursor(0,0);
		lcd.print("anas: %d",x);
		*/
		
		/*
		lcd.print(temp);
		
		x++;
		if(x==15){
			x=0;
			lcd.setCursor(1,0);
		}
		temp++;
		_delay_ms(1000);
		*/
		/*
		lcd.shift(LEFT,5,100);
		//lcd.home();
		_delay_ms(3000);
		lcd.shift(RIGHT,5,200);
		//lcd.home();
		_delay_ms(3000);
		*/
		/*
		lcd.setCursor(line,temp);
		temp++;
		_delay_ms(1000);
		if(temp >15){
			temp=0;
			line=1;
		}
			*/
		//PORTD ^= _BV(3);
		//_delay_ms(1000);
		//PORTC ^= _BV(0);
		//_delay_ms(1000);
    }
}

