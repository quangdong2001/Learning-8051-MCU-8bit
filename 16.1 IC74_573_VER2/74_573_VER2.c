#include "74_573_VER2.h"

unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}


void IC_74_573_VER2()
{
	while(1)
	{
		unsigned int i;
		for(i = 0; i < 100; i++)
		{
			
			// Hang Don Vi
			LED_SEGMENT = LED[i/10];
			LED1 = 1;
			LED1 = 0;
			
			//Hang Chuc
			LED_SEGMENT = LED[i%10];
			
			LED2 = 1;
			LED2 = 0;
			Sleep_ms(1000);
			
		}
	}
}