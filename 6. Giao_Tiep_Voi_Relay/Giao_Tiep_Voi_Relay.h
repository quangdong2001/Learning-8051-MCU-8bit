#ifndef _GIAO_TIEP_VOI_RELAY_H_
#define _GIAO_TIEP_VOI_RELAY_H

#include <regx52.h>

sbit ON_OFF = P3^0;
sbit Relay = P0^0;


void Delay(unsigned int t);
void Giao_Tiep_Voi_Relay();




#endif