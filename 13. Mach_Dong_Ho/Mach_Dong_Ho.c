#include "Mach_Dong_Ho.h"
unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Sleep_ms(unsigned int t)
{
	unsigned int a,b;
	for(a = 0; a < t; a++)
	{
		for(b = 0; b < 123; b++);
	}
}

void Mach_Dong_Ho()
{
	if(Button == 0)
	{
		unsigned char Hour, Minute, Second;
		unsigned char Chuc,Don_Vi;
		Hour = 0;
		Minute= 0;
		Second = 0;
		while(1)
		{
			unsigned int i;
			for(i = 0; i < 167; i++)
			{
			// HIEN THI GIO 
			Chuc = Hour / 10;
			Don_Vi = Hour % 10; 
			// Hien Thi Hang Chuc 
			LED_PORT = LED[Chuc];
			A1 = 0;
			Sleep_ms(1);
			A1 = 1;
			//Hien Thi Hang Don Vi 
			LED_PORT = LED[Don_Vi];
			B1 = 0;
			Sleep_ms(1);
			B1 = 1;
			
			// HIEN THI PHUT
			Chuc = Minute / 10;
			Don_Vi = Minute % 10;
			//Hien Thi Hang Chuc 
			LED_PORT = LED[Chuc];
			A2 = 0;
			Sleep_ms(1);
			A2 = 1;
			//Hien Thi Hang Don Vi 
			LED_PORT = LED[Don_Vi];
			B2 = 0;
			Sleep_ms(1);
			B2 = 1;
			
			// HIEN THI GIAY 
				
			Chuc = Second / 10;
			Don_Vi = Second % 10;
			// Hien Thi Hang Chuc 
			LED_PORT = LED[Chuc];
			A3 = 0;
			Sleep_ms(1);
			A3 = 1;
			
			// Hien Thi Hang Don Vi 
			LED_PORT = LED[Don_Vi];
			B3 = 0;
			Sleep_ms(1);
			B3 = 1;
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
						Hour = 0;
						Second = 0;
						Minute = 0;
					}
				}
			}
		}
	}
}