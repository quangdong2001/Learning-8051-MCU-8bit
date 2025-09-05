#ifndef _IC_2803_H
#define _IC_2803_H

#include <regx52.h>

sbit ON_OFF = P2^0;
sbit LED = P0^0;

void Delay(unsigned int t);
void IC_ULN2803();


#endif