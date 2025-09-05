#include "Library.h"


void ChopTatLed()
{
	unsigned int i,j;
	PORT_0 = 0x00;
	for(i = 0; i < 8; i++)
	{
		Delay(300);
		PORT_0 = PORT_0 << 1;
		PORT_0 = PORT_0 | (1 << 0);
	}
	Delay(300);
	PORT_0=0x00;
	for(j = 0; j < 8; j++)
	{
		Delay(300);
		PORT_0 = PORT_0 >> 1;
		PORT_0 = PORT_0 | (1 << 7);
	}
	Delay(300);
}
		


#if(FREQ_OSC == 12000000)
	void Delay(unsigned int t)
	{
		unsigned int i,j;
		for(i = 0; i < t; i++)
		{
				for(j = 0; j < 123; j++);
		}
	}

#elif(FREQ_OSC == 11059200)
	void Delay(unsigned int t)
	{
		unsigned int i,j;
		for(i = 0; i < t; i++)
		{
			for(j = 0; j < 113; j++);
		}	
	}		

#elif(FREQ_OSC == 40000000)
		void Delay(unsigned int t)
		{
			unsigned int i,j;
			for(i = 0; i < t; i++)
			{
				for(j = 0; j < 620; j++);
			}
		}
		
#elif(FREQ_OSC == 4000000)
		void Delay(unsigned int t)
		{
			unsigned int i,j;
			for(i = 0; i < t; i++)
			{
				for(j = 0; j < 40; j++);
			}
		}
		
#else 
		
		#error "Khong Ton Tai Ham Delay Nao Tuong Ung"
		
#endif
		
		


