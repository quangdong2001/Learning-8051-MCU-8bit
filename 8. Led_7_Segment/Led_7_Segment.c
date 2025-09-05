#include "Led_7_Segment.h"



void Delay(unsigned int t)
{
	unsigned int a,b;
	for(a = 0; a < t; a++)
	{
		for(b = 0; b < 123; b++);
	}
}

void LED_7_SEGMENT()
{
	unsigned char i,j;
	for(i = 0; i < 10; i++)
	{
		LED1= LED[i];
		for(j = 0; j < 10; j++)
		{
		LED2 = LED[j];
			Delay(1000);
		}
	}
}