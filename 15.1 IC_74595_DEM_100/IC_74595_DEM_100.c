#include "IC_74595_DEM_100.h"
unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

void Transmit(unsigned int *p,unsigned char size)
{
	unsigned char b,i,j;
	
	for(i = 0; i < size; i++)
	{
		b = *(p+size-1-i);
		for(j = 0; j < 8; j++)
		{
			DS = b & (0x80 >> j);
			
			SH_CP = 0;
			SH_CP = 1;
		}
	}
	ST_CP = 0;
	ST_CP = 1;
}

void IC_74595_DEM_100()
{
	unsigned char i;
	unsigned int arr[2];
	for(i = 0; i < 100; i++)
	{
		arr[0] = LED[i/10];
		arr[1] = LED[i%10];
		
		Transmit(arr,2);
		Sleep_ms(1000);
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

#elif (FREQ_OSC == 40000000)
void Sleep_ms(unsigned int t)
{
		unsigned int a,b;
		for(a = 0; a < t; a++)
		{
			for(b = 0; b < 165; b++);
		}
}

#elif (FREQ_OSC == 11059200)
void Sleep_ms(unsigned int t)
{
		unsigned int a,b;
		for(a = 0; a < t; a++)
		{
			for(b = 0; b < 95; b++);
		}
}
#else
	#error "KHONG TON TAI HAM Sleep_ms NAO THOAN MAN ~ !!"

#endif

	



	
	
	
	
	
	
	
	
	
	
	
	
	
	
	