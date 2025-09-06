#include "IC_74595.h"
unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Sleep_ms(unsigned int t)
{
	unsigned int a,b;
	for(a = 0; a < t; a++)
	{
		for(b = 0; b < 123; b++);
	}
}

void Transmit(unsigned int a)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		DS = a & (0x80 >> i);
		SH_CP = 0;
		SH_CP = 1;
	}
	ST_CP = 0;
	ST_CP =1;
}


void IC_74595()
{
	if(Button == 0)
	{
		// P0_0 = 0;
		while(1)
		{
			unsigned int i;
			for(i = 0; i < 10; i++)
			{
				Transmit(0x55);
				Sleep_ms(1000);
				Transmit(0xAA);
				Sleep_ms(1000);
			}
		}
	}
}