#ifndef _DEN_CAU_THANG_H_
#define _DEN_CAU_THANG_H_

#include <regx52.h>
#define FREQ_OSC 12000000

sbit PORT_UP = P1^0;
sbit PORT_DOWN = P2^0;
sbit LED_RED = P3^0;

void Delay(unsigned int t);
void Den_Cau_Thang();







#endif