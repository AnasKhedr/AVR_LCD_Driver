/*
 * LCD.h
 *
 * Created: 29-Mar-19 11:54:22 PM
 *  Author: Anas Khedr
 */ 


#ifndef LCD_H_
#define LCD_H_

#define WRITEONLY 1
typedef unsigned char uint8_t;


class MyLCD
{
public:
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t RW,uint8_t E);
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t D3,uint8_t D2,uint8_t D1,uint8_t D0,char Port_of_registers,uint8_t RS,uint8_t E);
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t RS,uint8_t RW,uint8_t E);
	MyLCD(char Port_of_D,uint8_t D7,uint8_t D6,uint8_t D5,uint8_t D4,uint8_t RS,uint8_t E);
	
	void command();
	void data();
	
	bool read();
	void write(char buffer);
	
	void upperWrite();
	void lowerWrite();
	void fullWrite();
	
	void send();
	
	void init(uint8_t Lines,uint8_t C,uint8_t B,uint8_t Resolution);
	void init(uint8_t Lines,uint8_t C,uint8_t B);
	void init(uint8_t Lines);
	
private:
	struct storage{
		uint8_t RS:3,RW:3,E:3,D0:3,D1:3,D2:3,D3:3,D4:3,D5:3,D6:3,D7:3,Port_of_D:4,Port_of_registers:4,wire_num:1,RW_Status:1;
		uint8_t buffer;
	}pins;
};




#endif /* LCD_H_ */