/*
 * GccApplication1.cpp
 *
 * Created: 02-Apr-19 11:38:15 PM
 * Author : anas
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include "LCD.h"
#include <util/delay.h>
#include "string.h"
#include <stdio.h>

int main(void){
    /* Replace with your application code */
	//MyLCD lcd('D',7,6,5,4,3,2,1,0,'B',0,1);
	MyLCD lcd('D',7,6,5,4,3,2);
	//_delay_ms(10);
	lcd.init(2,1,0);
	//_delay_ms(10);
	//lcd.data();
	//int age=5;
	//lcd.print("AGE: %d",age);
	//lcd.writeChar('A');
	//DDRC = 0x01;
	//char temp='0';
	//bool line=0;
	//char x=0;
	lcd.writeDirecion(0,0,0);
	lcd.print("anas ahmed fouad hassan khedr");
	lcd.command();
    while (1) 
    {
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
		
		lcd.shift(LEFT,5,100);
		//lcd.home();
		_delay_ms(3000);
		lcd.shift(RIGHT,5,200);
		//lcd.home();
		_delay_ms(3000);
		
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

