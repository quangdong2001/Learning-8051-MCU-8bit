#ifndef _IC_74595_DEM_100_H_
#define _IC_74595_DEM_100_H_
#include <regx52.h>

#define FREQ_OSC 12000000
sbit SH_CP = P0^0;
sbit ST_CP = P0^3;
sbit DS = P0^1;
void Sleep_ms(unsigned int t);
void Transmit(unsigned int *p,unsigned char size);
void IC_74595_DEM_100();


#endif