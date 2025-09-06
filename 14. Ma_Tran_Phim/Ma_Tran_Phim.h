#ifndef _MA_TRAN_PHIM_H_
#define _MA_TRAN_PHIM_H_

#include <regx52.h>

// Define Led
sbit LED1 = P3^0;
sbit LED2 = P3^1;

#define LED_PORT P0 

// Define Button
sbit Col1 = P1^0;
sbit Col2 = P1^1;
sbit Col3 = P1^2;
sbit Col4 = P1^3;
sbit Row1 = P1^4;
sbit Row2 = P1^5;
sbit Row3 = P1^6;
sbit Row4 = P1^7;

// Define Function

void Sleep_ms(unsigned int t);
unsigned char Key_Board();
void Board();
#endif