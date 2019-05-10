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
	int x=0;
	//lcd.writeDirecion(0,0,0);
	//lcd.print("anas ahmed fouad hassan khedr");
	lcd.command();
	//lcd.writeDirection(ENDADDRESS,0,RtoL);
	//lcd.print("anas: %d",x);
	//lcd.shiftR(0x18,100);
	
	struct tempx 
	{
		float x;
		char y;
	};
	
	lcd.command();
	lcd.clear();
	lcd.setCursor(0,0);
	/*
	//_delay_ms(20);
	lcd.command();
	lcd.writeChar(0x40 | 0);
	
	lcd.data();
	lcd.writeChar(0b01100);
	lcd.writeChar(0b01100);
	lcd.writeChar(0b01100);
	lcd.writeChar(0b01100);
	lcd.writeChar(0b01100);
	lcd.writeChar(0b01100);
	lcd.writeChar(0b01100);
	lcd.writeChar(0b01100);
	
	lcd.command();
	lcd.setCursor(0,0);
	lcd.data();
	lcd.writeChar((uint8_t)0);
	*/
	char customChar[7] = {14,27,24,30,27,27,14	};
	
	uint8_t d_ch=lcd.defineGraph(customChar);
	char customChar2[] = {10,10,31,31,14,4,4};
	uint8_t d_ch2=lcd.defineGraph(customChar2);
	lcd.command();
	lcd.setCursor(0,0);
	lcd.data();
	lcd.print("%d",(int)d_ch);
	lcd.writeChar(d_ch);
	lcd.writeChar(d_ch2);
	
    while (1) 
    {
		
		
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

