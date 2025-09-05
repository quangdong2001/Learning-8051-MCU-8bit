#ifndef _MACH_DONG_HO_H_
#define _MACH_DONG_HO_H_
// Add them thu vien 
#include <regx52.h>

// Define cac bit 
#define LED_PORT P2

sbit A1 = P3^0;
sbit B1 = P3^1;
sbit A2 = P3^2;
sbit B2 = P3^3;
sbit A3 = P3^4;
sbit B3 = P3^5;
sbit Button = P1^0;

// Define cac ham 

void Sleep_ms(unsigned int t);
void Mach_Dong_Ho();


#endif