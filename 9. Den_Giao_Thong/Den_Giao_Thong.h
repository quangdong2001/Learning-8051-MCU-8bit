#ifndef _DEN_GIAO_THONG_H_
#define _DEN_GIAO_THONG_H_
#include <regx52.h>

// Dinh nghia cac LED 7 Thanh
#define LED1 P0
#define LED2 P2

// Dinh nghia den Do Xanh Vang
sbit LED_RED = P3^0;
sbit LED_YELLOW = P3^1;
sbit LED_GREEN = P3^2;

// Cac ham cua Lib 
void Sleep_ms(unsigned int t);
void Den_Giao_Thong();



#endif