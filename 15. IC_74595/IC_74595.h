#ifndef _IC_74595_H_
#define _IC_74595_H_
#include <regx52.h>
sbit Button = P1^0;
sbit SH_CP = P2^0;
sbit ST_CP = P2^3;
sbit DS = P2^1;

void Sleep_ms(unsigned int t);
void Transmit(unsigned int a);
void IC_74595();
 



#endif 