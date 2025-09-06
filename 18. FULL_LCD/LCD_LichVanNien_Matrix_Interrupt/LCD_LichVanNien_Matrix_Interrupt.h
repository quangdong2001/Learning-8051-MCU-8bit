#ifndef _LCD_LICH_VAN_NIEN_MATRIX_INTERRUPT_H_
#define _LCD_LICH_VAN_NIEN_MATRIX_INTERRUPT_H_
#include <regx52.h>
// DS1307

sbit SDA = P1^0;
sbit SCL = P1^1;

#define SECOND 0x00
#define MINUTE 0x01
#define HOUR   0x02



// 74HC595
#define LED P0
sbit SH_CP = P2^0;
sbit DS    = P2^1;
sbit ST_CP = P2^3;

// Set Time

void Set_hour(unsigned char _hour);
void Set_minute(unsigned char _minute);
void Set_second(unsigned char _second);


// Sleep function 
void Sleep_ms(unsigned int t);

// 74HC595

void Send_Data(unsigned char a);

// DS1307

void DS1307_Start();
void DS1307_Stop();
void Write(unsigned char a);
unsigned char Read();
void DS1307_Write(unsigned char _address, unsigned char _data);
unsigned char DS1307_Read(unsigned char _address);


void LED_MATRIX();




#endif