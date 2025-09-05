#ifndef _LED_3_EFFECT_H_
#define _LED_3_EFFECT_H_

#include <regx52.h>
#define FREQ_OST 12000000

sbit START = P3^0;
sbit NEXT = P3^1;
#define LED P0

void Delay(unsigned int t);
void Led_3_Effect();
unsigned char Delay_Test();






#endif
