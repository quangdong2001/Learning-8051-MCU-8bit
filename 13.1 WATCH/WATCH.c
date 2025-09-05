#include "WATCH.h"

/// Khoi tao gia tri sang tu 0 - 9
unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};


void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
	
}


void WATCH()
{
	if(Button == 0)
	{
		unsigned char Hour, Minute, Second;
		Hour = 0;
		Minute = 0;
		Second = 0;
		while(1)
		{
				unsigned int i;
				for(i = 0; i < 166; i++)
				{
				/// Hien Thi Giay
				LED_PORT = LED[Second%10];
				LED6 = 0;
				Sleep_ms(1);
				LED6 = 1;
				LED_PORT = LED[Second/10];
				LED5  = 0;
				Sleep_ms(1);
				LED5 = 1;
				
				
				// Hien Thi Phut 
				
				LED_PORT = LED[Minute%10];
				LED4 = 0;
				Sleep_ms(1);
				LED4 = 1;
				LED_PORT = LED[Minute/10];
				LED3  = 0;
				Sleep_ms(1);
				LED3 = 1;
				
				// Hien Thi Gio 
				
				LED_PORT = LED[Hour%10];
				LED2 = 0;
				Sleep_ms(1);
				LED2 = 1;
				LED_PORT = LED[Hour/10];
				LED1  = 0;
				Sleep_ms(1);
				LED1 = 1;
				}	
				
				
				Second++;
				if(Second == 60)
				{
					Second = 0;
					Minute++;
					if(Minute == 60)
					{
						Minute = 0;
						Hour++;
						if(Hour == 24)
						{
							Hour  = 0;
							Minute = 0;
							Second = 0 ;
						}
					}
				}
		}
	}
}



