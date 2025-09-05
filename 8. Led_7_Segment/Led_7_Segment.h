#ifndef _LED_7_SEGMENT_H_
#define _LED_7_SEGMENT_H_
unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
#include <regx52.h>
#define LED1 P0
#define LED2 P2
void Delay(unsigned int t);
void LED_7_SEGMENT();

#endif