#include "IC_74573.h"
unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void IC_74573()
{
	while(1)
	{
		unsigned int i;
		LED1 = LED2 = LED3 = 0;
		for(i = 0; i < 1000; i++)
		{
			Control = LED[i / 100];
			LED1 = 1;
			LED1 = 0;
			Control = LED[(i/10)%10];
			LED2 = 1;
			LED2 = 0;
			Control = LED[i%10];
			LED3 = 1;
			LED3 = 0;
			Sleep_ms(50);
		}
	}
}


#if (FREQ_OSC == 12000000)
	void Sleep_ms(unsigned int t)
	{
		unsigned int a,b;
		for(a = 0; a < t; a++)
		{
			for(b = 0; b < 123; b++);
		}
	}
	
#elif (FREQ_OSC == 11059200)
	void Sleep_ms(unsigned int t)
	{
		unsigned int a,b;
		for(a = 0; a < t; a++)
		{
			for(b = 0, b < 96; b++);
		}
	}

#elif (FREQ_OSC == 40000000)
	void SLeep_ms(unsigned int t)
	{
		unsigned int a,b;
		for(a = 0; a < t; a++)
		{
			for(b = 0; b < 165; b++);
		}
	}

#else
	#error " KHONG TON TAI HAM SLEEP_MS NAO THOA MAN !! "

#endif