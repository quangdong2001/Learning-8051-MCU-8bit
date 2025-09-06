#ifndef _IC_74573_H_
#define _IC_74573_H_
#include <regx52.h>

#define Control P0
#define FREQ_OSC 12000000
sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;



void Sleep_ms(unsigned int t);
void IC_74573();


#endif 