#ifndef _74_573_VER2_H_
#define _74_573_VER2_H_
#include <regx52.h>

// Dinh nghia cac chan 
#define LED_SEGMENT P0
sbit LED1 = P2^0;
sbit LED2 =  P2^1;

// Ham 

void Sleep_ms(unsigned int t);
void IC_74_573_VER2();


#endif