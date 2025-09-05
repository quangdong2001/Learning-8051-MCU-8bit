#ifndef _IC_7447_H_
#define _IC_7447_H_
#include <regx52.h>
sbit Button = P1^0;

#define TRAM P0
#define CHUC P2
#define DON_VI P3

void Sleep_ms(unsigned int t);
void IC_7447();

#endif