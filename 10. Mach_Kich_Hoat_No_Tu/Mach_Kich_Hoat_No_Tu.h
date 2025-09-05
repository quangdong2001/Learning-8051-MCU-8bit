#ifndef _MACH_KICH_HOAT_NO_TU_H_
#define _MACH_KICH_HOAT_NO_TU_H_
#include <regx52.h>

// Dinh nghia cac cong de dieu khien 
#define LED1 P2
#define LED2 P3
sbit Button = P1^0;
sbit Activate = P0^0;

// Dinh nghia cac ham can thiet 
void Sleep_ms(unsigned int t);
void Kich_Hoat();

#endif