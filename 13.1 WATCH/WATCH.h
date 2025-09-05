#ifndef _WATCH_H_
#define _WATCH_H_
#include <regx52.h>
// Dinh nghia Chan Dieu Khien 
#define LED_PORT P0

sbit Button = P1^0;
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;
sbit LED5 = P2^4;
sbit LED6 = P2^5;


// Cac ham can thiet 
void Sleep_ms(unsigned int t);
void WATCH();
#endif