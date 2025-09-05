#ifndef _KIEM_TRA_DELAT_H_
#define _KIEM_TRA_DELAY_H_
#include <regx52.h>
#define FREQ_OSC 12000000

sbit START = P1^0;
sbit STOP = P1^1;
#define LED P0


void Delay(unsigned int t);
void Kiem_Tra_Delay();



#endif